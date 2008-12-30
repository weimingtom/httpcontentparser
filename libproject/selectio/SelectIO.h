#ifndef _UTILITY_SELECTIO_H__
#define _UTILITY_SELECTIO_H__

#include <httpcontentcheck.h>
#include <ws2spi.h>
#include <io.h>
#include <map>
#include <set>
#include <utility\protocolpacket.h>
#include <dnsmap.h>

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

class HTTPPacket;
class HTTP_RESPONSE_HEADER;
class SelectIOTest;


// buffer count
#define BUFFER_COM_ALL_COUNT 10

class SocketPackets {
public:
	typedef std::multimap<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
public:
	bool isAnyCompleteSOCKET();			// 是否已经有完成的IO
	void freeAllCompletedPacket(); // 释放所有已经完成的包
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);

	void getAllCompleteSOCKET(fd_set *readfds);	// 获取所有已经完成的IO的SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	int  removePacket(const SOCKET s, HTTPPacket *p);
	void clearAllPackets();		// 释放所有的包

	bool isThereUncompletePacket(const SOCKET s);

	// 使用新的包代替旧的包
	int replacePacket(SOCKET s, HTTPPacket *packet, HTTPPacket * new_packet);
protected:
	COMPLETED_PACKETS completed_packets_;	// 保存于SOCKET对应已经完成的数据包
	SOCK_DATA_MAP _sockets_map_;			// 保存正在处理的数据包

	// 临界区
	yanglei_utility::CAutoCreateCS cs_;

	friend class SelectIOTest;
};

// 保存包检测的结果
// 如果一个包在完成接受之后，可能还要分成多个包向上层程序传送
// 这时候会产生一个错误: 这个包的内容会被检测多次， 检测的同时有
// 会被保存多次。 为了修复这个错误，我们缓存一下这个包的结果。
// 这个值应该在handlePacket添加或查询
// 在removePacket时移除
class BufferResult {
public:
	bool getResult(int code, int * result); 
	void addResultPair(int code, int result);
	void removeBufferResult(HTTPPacket *packet);
	void removeAllBufferResult() {content_check_result_.clear();}

private:
	typedef std::map<int, int> BUFFER_RESULT;
	BUFFER_RESULT content_check_result_;

	// 临界区
	yanglei_utility::CAutoCreateCS cs_;
};

class CSelectIO {
public:
	CSelectIO();
	~CSelectIO(void);

	// 在调用selelect之前调用，如果返回0,则select函数，应该直接返回(表示存在已经完成的包)
	int preselect(fd_set *readfds);
	int postselect(fd_set *readfds);


	// 在调用WSPRecv之前调用
	// 如果prerecv返回0， 代表他已经放入了数据, 不需要在调用WSPRecv了
	// 如果返回其他， 则代表我们没有已经完成的包，此时可以调用WSPRecv
	int prerecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, DWORD *recv_bytes);

	void onCloseSocket(const SOCKET s);

	void setRecv(MYWSPRECV *recv);

	bool checkWhiteDNS(SOCKET s);
protected: 
	
	//==========================================
	// 处理正在传输的包
	bool needStored(const SOCKET s); // 是不是需要处理的包
	int  graspData(const SOCKET s, char *buf, const int len);

	// 保存WSPRecv的函数指针
	MYWSPRECV * lpWSPRecv;
	friend class SelectIOTest;

// 检查包的的内容
	bool handlePacket(HTTPPacket *packet);

	SocketPackets socketPackets_;
	BufferResult   bufferResult_;
protected:
	HTTPContentHander handler_;

public:
	void addDNS(SOCKET s, const std::string &addr);
private:
		// dns MAP
	DNSMap	dnsmap_;
	// 移除dns MAP
	void removeDNSMap(SOCKET s);
};

// utility functions
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount);
int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len);

#endif  // _UTILITY_SELECTIO_H__
