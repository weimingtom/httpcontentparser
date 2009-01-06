#ifndef _UTILITY_SELECTIO_H__
#define _UTILITY_SELECTIO_H__

#include <httpcontentcheck.h>
#include <ws2spi.h>
#include <io.h>
#include <map>
#include <set>
#include <utility\protocolpacket.h>
#include <dnsmap.h>
#include <WebsiteRecorder.h>
#include <bufferresult.h>
#include <HandleQueue.h>
#include <socketpackets.h>

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
protected:
	HandleQueue	packet_handle_queue_;

	// 用于记录网站地址
	WebsiteRecorder website_recorder_;
public:
	void addDNS(SOCKET s, const std::string &addr);
	
	// 在DLL卸载时调用
	void finalize();
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
