#include "StdAfx.h"
#include ".\socketpackets.h"
#include ".\handlequeue.h"

//=================================================
// class SocketPackets;
// 查看是否存在已经完成的包
bool SocketPackets::isAnyCompleteSOCKET() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	return completed_packets_.size() != 0;
}

// 将所有已经有完成包的socket存放在fd_set当中
// 此函数一般会在preselect中调用
void SocketPackets::getAllCompleteSOCKET(fd_set *readfds, HandleQueue * handler) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	int handle_result;
	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	while ( iter != completed_packets_.end()) {
		FD_SET(iter->first, readfds);
		
		// 不只包完整， 且数据需要处理完全
		if (handler->getResult(iter->second, &handle_result))
			iter = completed_packets_.upper_bound(iter->first);
	}
}

// 将与SOCKET对应HTTPPacket的包添加到完成队列当中
int SocketPackets::addCompletedPacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	completed_packets_.insert(std::make_pair(s, p));
	return 0;
}

// 获取与SOCKET对应第一个已经完成的包
HTTPPacket * SocketPackets::getCompletedPacket(const SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	COMPLETED_PACKETS::iterator iter = completed_packets_.find(s);
	if (completed_packets_.end() == iter) {
		return NULL;
	} else {
		return iter->second;
	}
}

int SocketPackets::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	//SingleLock<CAutoCreateCS> lock(&cs_);

	// OutputDebugString("remove complete socket");
	COMPLETED_PACKETS::iterator iter = completed_packets_.begin();
	COMPLETED_PACKETS::const_iterator iterEnd = completed_packets_.end();
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
			delete p;		// **** 把这个忘了，导致内存泄漏
			completed_packets_.erase(iter);
			return 1;
		}
	}
	return 0; 
}

void SocketPackets::freeAllCompletedPacket() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	for (; iter != completed_packets_.end(); ++iter) {
		if (iter->second != NULL) {
			delete iter->second;
		}
	}
	completed_packets_.clear();
}

// 删除掉所有保存的临时包
void SocketPackets::clearAllPackets() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// char buffer[1024];
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) {
			delete iter->second;
		}
	}
	_sockets_map_.clear();
}

bool SocketPackets::isThereUncompletePacket(const SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	return _sockets_map_.find(s) != _sockets_map_.end();
}

// 获取与SOCKET相关的未完成的包
HTTPPacket * SocketPackets::getSOCKETPacket(const SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DATA_MAP::iterator iter = _sockets_map_.lower_bound(s);
	SOCK_DATA_MAP::iterator iterEnd = _sockets_map_.upper_bound(s);
	for (; iter != iterEnd; ++iter) {
		// 这里为什么会出现完成的包呢 ??
		assert (iter->second->isComplete() == false);
		return iter->second;
	}
	
	HTTPPacket *packet = new HTTPPacket;
	_sockets_map_.insert(std::make_pair(s, packet));

	return packet;	
}
//int socketpackets::replacepacket(socket s, httppacket *p, httppacket * new_packet) {
//	using namespace yanglei_utility;
//	singlelock<cautocreatecs> lock(&cs_);
//
//	sock_data_map::iterator iter = _sockets_map_.lower_bound(s);
//	sock_data_map::const_iterator iterend = _sockets_map_.upper_bound(s);
//	for (; iter != iterend; ++iter) {
//		if (iter->second->getcode() == p->getcode()) {
//			assert(s == iter->first);
//			iter->second = new_packet;
//			return 1;
//		}
//	}
//
//	return 0;
//}
int SocketPackets::removePacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DATA_MAP::iterator iter = _sockets_map_.lower_bound(s);
	SOCK_DATA_MAP::const_iterator iterEnd = _sockets_map_.upper_bound(s);
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
			//char buffer[1024];
			//sprintf(buffer, "== remove socket : %d, code : %d", s, p->getCode());
			//OutputDebugString(buffer);
			assert(s == iter->first);
			_sockets_map_.erase(iter);
			return 1;
		}
	}

	assert(false);
	return 0; 
}
