#ifndef _SELECTIO_SOCKETPACKETS_H__
#define _SELECTIO_SOCKETPACKETS_H__

#include <httpcontentcheck.h>
#include <ws2spi.h>
#include <io.h>
#include <map>
#include <set>
#include <utility\protocolpacket.h>
#include <dnsmap.h>
#include <WebsiteRecorder.h>


class BufferResult;
class HandleQueue;

class SocketPackets {
public:
	bool isAnyCompleteSOCKET();			// �Ƿ��Ѿ�����ɵ�IO
	void freeAllCompletedPacket(); // �ͷ������Ѿ���ɵİ�
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);

	void getAllCompleteSOCKET(fd_set *readfds, HandleQueue * handler);	// ��ȡ�����Ѿ���ɵ�IO��SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	int  removePacket(const SOCKET s, HTTPPacket *p);
	void clearAllPackets();		// �ͷ����еİ�

	bool isThereUncompletePacket(const SOCKET s);

	// �Ƴ�������S��صİ�
	void removeSocketRel(const SOCKET s, BufferResult * result);

	// ʹ���µİ�����ɵİ�
	// int replacePacket(SOCKET s, HTTPPacket *packet, HTTPPacket * new_packet);
private:
	typedef std::multimap<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
private:

	COMPLETED_PACKETS completed_packets_;	// ������SOCKET��Ӧ�Ѿ���ɵ����ݰ�
	SOCK_DATA_MAP _sockets_map_;			// �������ڴ�������ݰ�

	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;

	friend class SelectIOTest;
};

#endif  // _SELECTIO_SOCKETPACKETS_H__
