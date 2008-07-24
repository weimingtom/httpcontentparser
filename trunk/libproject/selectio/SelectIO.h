#ifndef _UTILITY_SELECTIO_H__
#define _UTILITY_SELECTIO_H__

#include <ws2spi.h>
#include <io.h>
#include <map>
#include <set>
#include <utility\protocolpacket.h>

typedef int WSPAPI MYWSPRECV(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesRecvd,
	LPDWORD			lpFlags,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
);

typedef int WSPAPI MYCLOSESOCKET(
	SOCKET		s,
	LPINT		lpErrno
);


class HTTPPacket;
class HTTP_RESPONSE_HEADER;
class SelectIOTest;

// class CheckSetting
// 此类是一个单件类， 我们使用它来保存规则(那些类型的HTTP包学要被处理)
class CheckSetting {
public:
	static CheckSetting * getInstance() {
		static CheckSetting setting;
		return &setting;
	}
	~CheckSetting();

	// 是否需要处理
	bool needCheck(const int type);

	// 添加规则
	void addCheckedType(const int type);

	// 移除removeCheckedType
	bool removeCheckedType(const int type);
private:
	CheckSetting();
	typedef std::set<int> CHECKED_TYPES;
	CHECKED_TYPES http_types_;
};

class CSelectIO {
public:
	CSelectIO();
	~CSelectIO(void);

	// 在调用selelect之前调用，如果返回0,应该直接返回(表示存在已经完成的包)
	int preselect(fd_set *readfds);
	int postselect(fd_set *readfds);


	// 在调用WSPRecv之前调用
	// 如果prerecv返回0， 代表他已经放入了数据, 不需要在调用WSPRecv了
	// 如果返回其他， 则代表我们没有已经完成的包，此时可以调用WSPRecv
	int prerecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, DWORD *recv_bytes);

	bool checkWholePacket(HTTPPacket * packet);

	int onCloseSocket(const SOCKET s);

	void setCloseSocket(MYCLOSESOCKET *lpWSPCloseSocket);
	void setRecv(MYWSPRECV *recv);
protected:
	// 是否需要处理
	bool isneedToDeal(HTTP_RESPONSE_HEADER * header);
	// 
	bool isThereUncompletePacket(const SOCKET s);
	//==========================================
	// 处理正在传输的包
	typedef std::multimap<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	SOCK_DATA_MAP _sockets_map_;
	void clearAllPackets();		// 释放所有的包
	bool needStored(const SOCKET s); // 是不是需要处理的包
	int  graspData(const SOCKET s, char *buf, const int len);
	int  addHttpPacket(const SOCKET s, char *buf, const int len);
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	int  removePacket(const SOCKET s, HTTPPacket *p);

	//==========================================
	// 处理已经完成传输的包
	void getAllCompleteSOCKET(fd_set *readfds);	// 获取所有已经完成的IO的SOCKET
	bool isAnyCompleteSOCKET();			// 是否已经有完成的IO
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void freeAllCompletedPacket();		// 释放所有的已经完成的包， 只在析构函数中调用
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
	COMPLETED_PACKETS completed_packets_;

	yanglei_utility::CAutoCreateCS cs_;

	// 保存WSPRecv的函数指针
	MYWSPRECV * lpWSPRecv;
	MYCLOSESOCKET *lpWSPCloseSocket;

	friend class SelectIOTest;

	// 等待关闭的
	typedef std::set<SOCKET> SOCKET_SET;
	SOCKET_SET wait_for_closed_;
	void closeSocket(const SOCKET s);
	void addCloseSocket(const SOCKET s);
};

// utility functions
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount);
int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len);

#endif  // _UTILITY_SELECTIO_H__
