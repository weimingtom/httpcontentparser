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

	// �ڵ���selelect֮ǰ���ã��������0,��select������Ӧ��ֱ�ӷ���
	int preselect(fd_set *readfds);
	int postselect(fd_set *readfds);
	// �ڵ��õ�ʱ��
	int prerecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, DWORD *recv_bytes);

	bool checkWholePacket(HTTPPacket * packet);

	void onCloseSocket(const SOCKET s);

	void setRecv(MYWSPRECV *recv) { lpWSPRecv = recv;}
protected:
	//==========================================
	// �������ڴ���İ�
	typedef std::map<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	typedef std::map<SOCKET, INT>	SOCK_ERROR;
	SOCK_DATA_MAP _sockets_map_;
	void clearAllPackets();		// �ͷ����еİ�
	bool needStored(const SOCKET s); // �ǲ�����Ҫ����İ�
	int  graspData(const SOCKET s, char *buf, const int len);
	int  addHttpPacket(const SOCKET s, char *buf, const int len);
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	void setSOCKETPacket(const SOCKET s, HTTPPacket * packet);


	//==========================================
	// �����Ѿ���ɴ���İ�
	void getAllCompleteSOCKET(fd_set *readfds);	// ��ȡ�����Ѿ���ɵ�IO��SOCKET
	bool isAnyCompleteSOCKET();			// �Ƿ��Ѿ�����ɵ�IO
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void freeAllCompletedPacket();		// �ͷ����е��Ѿ���ɵİ��� ֻ�����������е���
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
	COMPLETED_PACKETS completed_packets_;

	yanglei_utility::CAutoCreateCS cs_;

	// ����WSPRecv�ĺ���ָ��
	MYWSPRECV * lpWSPRecv;
};

#endif  // _UTILITY_SELECTIO_H__
