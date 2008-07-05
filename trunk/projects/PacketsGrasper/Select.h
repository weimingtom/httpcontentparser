#ifndef _PACKETS_GRASPER_SELECT_H__
#define _PACKETS_GRASPER_SELECT_H__

#include <set>
#include <map>
#include <utility\ProtocolPacket.h>
#include <utility\httpPacket.h>
#include <utility\syncutility.h>

const int DEFAULT_SIZE = 4 * 1024;

// ���𱣴������Ѿ���ɵ�Packets
class FinishedPackets {
public:
	HTTPPacket *getFinishedPacket(const SOCKET s);
private:
	typedef std::multimap<SOCKET , HTTPPacket *> FINISHED_PACKETS_MAP;
	FINISHED_PACKETS_MAP packets_;
};
// ��SELECT I/Oģ�ʹ���Ļ����뷨��
// �ڵ���select����ʱ�����Ƿ�������fd_read_set�е�SOCKET
// ��֮����HTTP������������SOCKET����������ָ�����
// SOCKET�ܵ��������������������������з���
// Ȼ�������뵽�µķ��ص�select����
// ������WSPRecv�ж԰����д���

// ����select I\O
// ��select����ʱ����Ӧ�ý����Է��ص�socket���أ�
// ��Ӧ�ñ�����select��Ϣ����������֮�����Ǽ���������Ϣ
// ֪����Ϣ�а����㹻����Ϣ�����Ǵ���


class CSelect {
public:
	CSelect(void);
	~CSelect(void);
public:
	// �˺���Ӧ����closesocket�е���
	void removeSocket(const SOCKET s);
	int analyRecvData(LPWSABUF lpBuffers,  const DWORD bytes_read, const SOCKET s);
	int post_recv(LPWSABUF lpBuffers,  LPDWORD bytes_read, const SOCKET s);
	int pre_select(fd_set *readfds);
	bool isFakeSelect(const SOCKET s) { return fake_select_;}
private:	
	typedef std::map<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	SOCK_DATA_MAP _sockets_map_;
	void freeAllPackets();
	typedef std::map<SOCKET, int> SOCK_DATA_READ;
	SOCK_DATA_READ sock_data_read_;
	
	// ��������Ƿ񷵻�
	int checkData(HTTPPacket *packet, const SOCKET s);

	// ��ȡ��SOCKET���Ӧ�����ݰ�
	HTTPPacket* createSOCKETPacket(const SOCKET s); // ����������򴴽�
	HTTPPacket* getSOCKETPacket(const SOCKET s);	// ��������ڷ���NULL

	// ��������
	HTTPPacket* checkContent(const SOCKET s);

	// ץȡ���ݣ�������ݲ�����Ҫ����ֱ���ͷ�
	int grasperData(const char * buf, const int len, HTTPPacket *packet);

	// �����ݴ洢��ָ������������
	int releaseData(char *buf, const int len, const SOCKET s);

	// �˺��������s�����жϣ��Ƿ�ѧҪ��������
	// ���᷵��
	// SELECT_CHECK_NEEDED, SELECT_CHECK_NEEDLESS,��SELECT_CHECK_UNKNOWN
	int needChecker(const SOCKET s);

	// ����ȡ������Ϣ���뻺����
	int peekMessage(char *buf, const int len, const SOCKET s);

	// �Ƿ���Ҫ����
	bool needStored(HTTPPacket *packet);
public:
	static const REMOVE_SOCKET_ = 0;	// �ͷ�SOCKET

	// CheckDataContentʱ�ķ���ֵ
	static const SELECT_CHECK_DENY	= 0; // 
	static const SELECT_CHECK_PASSED = 1;
	static const SELECT_CHECK_NOCHECK = 2;

	static const SELECT_CHECK_NEEDLESS = 0; // ���ݲ���Ҫ�����
	static const SELECT_CHECK_NEEDED = 1;   // ������Ҫ�����
	static const SELECT_CHECK_UNKNOWN = 2;  // δ֪

	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void freeAllCompletedPacket();
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
	COMPLETED_PACKETS completed_packets_;

	yanglei_utility::CAutoCreateCS cs_;

	bool fake_select_;
public:
	void Dump(const SOCKET s);					// Dmp��s��ص����а�
	void Dump(const SOCKET s, HTTPPacket *);	// Dump HTTPPacket, ������SOCKET���
};

#endif  // _PACKETS_GRASPER_SELECT_H__