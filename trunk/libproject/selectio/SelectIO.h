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

	// �ڵ���selelect֮ǰ���ã��������0,��select������Ӧ��ֱ�ӷ���(��ʾ�����Ѿ���ɵİ�)
	int preselect(fd_set *readfds);
	int postselect(fd_set *readfds);


	// �ڵ���WSPRecv֮ǰ����
	// ���prerecv����0�� �������Ѿ�����������, ����Ҫ�ڵ���WSPRecv��
	// ������������� ���������û���Ѿ���ɵİ�����ʱ���Ե���WSPRecv
	int prerecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, DWORD *recv_bytes);

	void onCloseSocket(const SOCKET s);

	void setRecv(MYWSPRECV *recv);

	bool checkWhiteDNS(SOCKET s);
protected: 
	
	//==========================================
	// �������ڴ���İ�
	bool needStored(const SOCKET s); // �ǲ�����Ҫ����İ�
	int  graspData(const SOCKET s, char *buf, const int len);

	// ����WSPRecv�ĺ���ָ��
	MYWSPRECV * lpWSPRecv;
	friend class SelectIOTest;

// �����ĵ�����
	bool handlePacket(HTTPPacket *packet);
protected:
	HandleQueue	packet_handle_queue_;

	// ���ڼ�¼��վ��ַ
	WebsiteRecorder website_recorder_;
public:
	void addDNS(SOCKET s, const std::string &addr);
	
	// ��DLLж��ʱ����
	void finalize();
private:
		// dns MAP
	DNSMap	dnsmap_;
	// �Ƴ�dns MAP
	void removeDNSMap(SOCKET s);
};

// utility functions
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount);
int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len);

#endif  // _UTILITY_SELECTIO_H__
