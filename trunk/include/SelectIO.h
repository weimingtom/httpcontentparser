#ifndef _UTILITY_SELECTIO_H__
#define _UTILITY_SELECTIO_H__

#include <map>
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

class HTTPPacket;
class CSelectIO {
public:
	CSelectIO();
	~CSelectIO(void);

	// 在调用selelect之前调用，如果返回0,则select函数，应该直接返回
	int preselect(fd_set *readfds);
	int postselect(fd_set *readfds);
	// 在调用的时候
	int prerecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, DWORD *recv_bytes);

	bool checkWholePacket(HTTPPacket * packet);

	void onCloseSocket(const SOCKET s);

	void setRecv(MYWSPRECV *recv) { lpWSPRecv = recv;}
protected:
	//==========================================
	// 处理正在传输的包
	typedef std::map<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	typedef std::map<SOCKET, INT>	SOCK_ERROR;
	SOCK_DATA_MAP _sockets_map_;
	void clearAllPackets();		// 释放所有的包
	bool needStored(const SOCKET s); // 是不是需要处理的包
	int  graspData(const SOCKET s, char *buf, const int len);
	int  addHttpPacket(const SOCKET s, char *buf, const int len);
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	void setSOCKETPacket(const SOCKET s, HTTPPacket * packet);


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
};

#endif  // _UTILITY_SELECTIO_H__
