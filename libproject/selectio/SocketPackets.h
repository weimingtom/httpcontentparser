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
	bool isAnyCompleteSOCKET();			// 是否已经有完成的IO
	void freeAllCompletedPacket(); // 释放所有已经完成的包
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);

	void getAllCompleteSOCKET(fd_set *readfds, HandleQueue * handler);	// 获取所有已经完成的IO的SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	int  removePacket(const SOCKET s, HTTPPacket *p);
	void clearAllPackets();		// 释放所有的包

	bool isThereUncompletePacket(const SOCKET s);

	// 移除所有与S相关的包
	void removeSocketRel(const SOCKET s, BufferResult * result);

	// 使用新的包代替旧的包
	// int replacePacket(SOCKET s, HTTPPacket *packet, HTTPPacket * new_packet);
private:
	typedef std::multimap<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
private:

	COMPLETED_PACKETS completed_packets_;	// 保存于SOCKET对应已经完成的数据包
	SOCK_DATA_MAP _sockets_map_;			// 保存正在处理的数据包

	// 临界区
	yanglei_utility::CAutoCreateCS cs_;

	friend class SelectIOTest;
};

#endif  // _SELECTIO_SOCKETPACKETS_H__
