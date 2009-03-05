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
	bool isAnyCompleteSOCKET();			// �Ƿ��Ѿ�����ɵ�IO
	void freeAllCompletedPacket(); // �ͷ������Ѿ���ɵİ�
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);

	void getAllCompleteSOCKET(fd_set *readfds);	// ��ȡ�����Ѿ���ɵ�IO��SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	int  removePacket(const SOCKET s, HTTPPacket *p);
	void clearAllPackets();		// �ͷ����еİ�

	bool isThereUncompletePacket(const SOCKET s);

	// ʹ���µİ�����ɵİ�
	int replacePacket(SOCKET s, HTTPPacket *packet, HTTPPacket * new_packet);
protected:
	COMPLETED_PACKETS completed_packets_;	// ������SOCKET��Ӧ�Ѿ���ɵ����ݰ�
	SOCK_DATA_MAP _sockets_map_;			// �������ڴ��������ݰ�

	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;

	friend class SelectIOTest;
};

// ��������Ľ��
// ���һ��������ɽ���֮�󣬿��ܻ�Ҫ�ֳɶ�������ϲ������
// ��ʱ������һ������: ����������ݻᱻ����Σ� ����ͬʱ��
// �ᱻ�����Ρ� Ϊ���޸�����������ǻ���һ��������Ľ����
// ���ֵӦ����handlePacket���ӻ��ѯ
// ��removePacketʱ�Ƴ�
class BufferResult {
public:
	bool getResult(int code, int * result); 
	void addResultPair(int code, int result);
	void removeBufferResult(HTTPPacket *packet);
	void removeAllBufferResult() {content_check_result_.clear();}

private:
	typedef std::map<int, int> BUFFER_RESULT;
	BUFFER_RESULT content_check_result_;

	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;
};

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
	bool needStored(const SOCKET s); // �ǲ�����Ҫ�����İ�
	int  graspData(const SOCKET s, char *buf, const int len);

	// ����WSPRecv�ĺ���ָ��
	MYWSPRECV * lpWSPRecv;
	friend class SelectIOTest;

// �����ĵ�����
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
	// �Ƴ�dns MAP
	void removeDNSMap(SOCKET s);
};

// utility functions
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount);
int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len);

#endif  // _UTILITY_SELECTIO_H__