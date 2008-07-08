#ifndef _UTILITY_SELECTIO_H__
#define _UTILITY_SELECTIO_H__

#include <ws2spi.h>
#include <io.h>		
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
class HTTP_RESPONSE_HEADER;


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

	void setRecv(MYWSPRECV *recv);

	class ContentCheckSetting {
	public:
		ContentCheckSetting();
		~ContentCheckSetting(){}

		bool CheckContent(HTTP_RESPONSE_HEADER * header);
		void setCheckHTML(const bool check);
		void setCheckXML(const bool check);
		void setCheckImage(const bool check);
		void setCheckImageSize(const int minsize, const int maxsize);
	private:
		bool checkImage_;
		bool checkHTML_;
		bool checkXML_;
		int  minImageSize_, maxImageSize_;
	};
	ContentCheckSetting checkSetting_;
protected:
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
};

// utility functions
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount);
int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len);

#endif  // _UTILITY_SELECTIO_H__
