#include "stdafx.h"
#include ".\select.h"
#include "debug.h"
#include <winsock2.h>
#include <map>
#include <logutility.h>
#include <utility\ProtocolPacket.h>
#include <utility\HttpContentChecker.h>
#include <utility\fd_set_utility.h>

extern WSPPROC_TABLE		NextProcTable;	


//====================================
// class CSelect
CSelect::CSelect(void) {
	fake_select_ = false;
}

CSelect::~CSelect(void) {
	freeAllCompletedPacket();
	freeAllPackets();
}


void CSelect::removeSocket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (_sockets_map_.end() != iter ) {
	//	// 删除为socket分配的缓冲区
		if (iter->second != NULL) 
			delete iter->second;
		// 删除socket
		_sockets_map_.erase(iter);
	}
}


int CSelect::pre_select(fd_set *readfds) {
	if (readfds == NULL)
		return 0;

	if (completed_packets_.size() == 0) {
		fake_select_ = false;
		return 0;
	}

	FD_ZERO(readfds);
	COMPLETED_PACKETS::iterator iter = completed_packets_.begin();
	for (; iter != completed_packets_.end(); ++iter) {
		FDSET_Add(readfds, iter->first);
	}

	fake_select_ = true;

	return 1;
}

int CSelect::post_recv(LPWSABUF lpBuffers,  LPDWORD bytes_read, const SOCKET s) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);

		HTTPPacket * packet = getCompletedPacket(s);
		if (NULL != packet) {
			// 将数据写入
			// 保存的包是已经解析过得，因此必须进行改变
			const rest_bytes = packet->read(lpBuffers->buf, 
				lpBuffers->len, (int&)*bytes_read);
			if (rest_bytes == 0) {
				removeCompletedPacket(s, packet);
			}
		}

		return 0;
	} catch (...) {
		return 0;
	}
}

int CSelect::analyRecvData(LPWSABUF lpBuffers, const DWORD bytes_read, const SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	const int check_result = needChecker(s);
	if (check_result == SELECT_CHECK_NEEDLESS)
		return 0;

	// 存储数据
	const int bytes_stored = peekMessage(lpBuffers->buf, bytes_read, s);
	if (bytes_stored == 0)
		return 0;


	// 验证数据
	HTTPPacket* packet = checkContent(s);
	if (NULL != packet) {
		Dump(s, packet);
		// 如果通过验证，将数据包加入到
		addCompletedPacket(s, packet);
		
	} else {
		return 0;
	}

	// 这里并不修改缓冲区
	return 1;
}

HTTPPacket* CSelect::getSOCKETPacket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (iter == _sockets_map_.end()) {
		return NULL;
	} else {
		return iter->second;
	}
}

// 检测SOCKET 是否需要处理
// 如果已经保存在map当中那么直接返回对应的HTTPPacket
// 否则， 创建一个并保存在map当中
// 注意如果返回NULL, 表明SOCKET不需要处理。
HTTPPacket* CSelect::createSOCKETPacket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	HTTPPacket* sock_data  = NULL;
	if (iter == _sockets_map_.end()) {		
		sock_data = new HTTPPacket;
		_sockets_map_.insert(std::make_pair(s, sock_data));
	} else {
		sock_data = iter->second;
	}
	return sock_data;
}

HTTPPacket* CSelect::checkContent(const SOCKET s) {
	HTTPPacket *sock_data = getSOCKETPacket(s);
	assert(s != NULL);
	// 万一等于这个呢.....
	if (s == NULL) return NULL;

	// 如果包已经完成，则验证数据
	// 如果通过，则从数据链中取出，并返回对应指针
	// 如果未通过则返回NULL
	if (sock_data->isComplete()) {
		const int result_check =  checkData(sock_data, s);
		if (HttpContentChecker::CHECK_PASSED == result_check) {
			// 审查通过()
			HTTPPacket *packet = sock_data->detachNext();
			if (packet == NULL) {
				// 如果不存在下一个包，那么移除socket****
				// 如果不移除会，下次将不会处理包，因此必须移除
				_sockets_map_.erase(s);
			} else {
				_sockets_map_[s] = packet;
			}
			return sock_data;
		} else /*if (HttpContentChecker::CHECK_DENYED == result_check) */{
			// 未通过审查
			// 生成一个错误404包，发给相关socket
			return NULL;
		}
	} else { // 如果包还不完整
		return NULL;
	}
}

// 是否需要保存
bool CSelect::needStored(HTTPPacket *packet) {
	if (HttpContentChecker::needCheck(packet) 
			== HttpContentChecker::CHECK_NEEDLESS)
		return false;
	else 
		return true;
}

// 处理数据包
// 检查数据包是否完整，必须保证包是完整的
int CSelect::checkData(HTTPPacket *packet, const SOCKET s) {
	// 如果包学要处理，则检查包内容
	return HttpContentChecker::checkContent(packet);
}

// 此函数确定从SOCKET S上受到的信息是否需要验证
// 如果不学要验证则直接释放
// 否则加入到存储内，并在包完整以后进行验证。
int CSelect::peekMessage(char *buf, const int len, const SOCKET s) {
	try {
		HTTPPacket* sock_data = createSOCKETPacket(s);
		if (sock_data == NULL) {
			// 有两种可能性，创建失败，或者不符合要求
			return 0;
		} else {
			// 将数据存入
			const int byte_stored = sock_data->addBuffer(buf, len);
			// 做简单的类型判定
			if (false == needStored(sock_data)) {
				delete sock_data;
				_sockets_map_[s] = NULL;
				return 0;
			}
			return byte_stored;
		} 
	} catch (std::bad_alloc &) {
		writeException("CSelect::storeMessage", "std::bad_alloc");
		DebugStringNoDres("CSelect::storeMessage bad_alloc.");
		return 0;
	} catch (...) {
		DebugStringNoDres("CSelect::storeMessage failed..");
		writeException("CSelect::storeMessage", "Unknown exception");
		return 0;
	}
}

int CSelect::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	COMPLETED_PACKETS::iterator iter = completed_packets_.lower_bound(s);
	COMPLETED_PACKETS::iterator iterEnd = completed_packets_.upper_bound(s);

	// 查找，如果存咋则删除
	for (; iter != iterEnd; ++iter) {
		if (iter->second == p) {
			completed_packets_.erase(iter);
			return 1;
		}
	}
	return 0;
}

void CSelect::freeAllPackets() {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) 
			Dump(iter->first, iter->second);
			delete iter->second;
	}
	_sockets_map_.clear();
}
void CSelect::freeAllCompletedPacket() {
	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	for (; iter != completed_packets_.end(); ++iter) {
		delete iter->second;
	}
	completed_packets_.clear();
}

int CSelect::addCompletedPacket(const SOCKET s, HTTPPacket *p) {
	completed_packets_.insert(std::make_pair(s, p));
	return 0;
}

HTTPPacket * CSelect::getCompletedPacket(const SOCKET s) {
	COMPLETED_PACKETS::iterator iter = completed_packets_.lower_bound(s);
	if (completed_packets_.end() == iter) {
		return NULL;
	} else {
		return iter->second;
	}
}

// 测试是否学要处理
// 如果在map中与S对应的value == NULL,
// 那么就不学要处理
int CSelect::needChecker(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (iter == _sockets_map_.end()) {		
		// 未从map中找到数据， 那么socket的类型是未知的
		return SELECT_CHECK_UNKNOWN;
	} else if (iter->second == NULL) {
		// 如果与socket对应的值是NULL, 那么socket不需要处理
		return SELECT_CHECK_NEEDLESS;
	} else {
		// 如果找到了包，那么学要处理
		return SELECT_CHECK_NEEDED;
	}
}


#ifndef NO_SAVE_SEELCT_IO_DATA
void CSelect::Dump(const SOCKET s, HTTPPacket *packet) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	assert(packet != NULL);
	const int bufsize = 1024;
	char buffer[bufsize];

	_snprintf(buffer, bufsize, "F:\\project\\net\\%d%X_header.log", s, packet);
	packet->achieve_header(buffer);
	_snprintf(buffer, bufsize, "F:\\project\\net\\%d%X_data.log", s, packet);
	packet->achieve_data(buffer);
}
void CSelect::Dump(const SOCKET s) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	// 初始化缓冲区 
	const int bufsize = 1024;
	char buffer[bufsize];
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (iter != _sockets_map_.end() && iter->second != NULL) {
		if (iter->second) {
			_snprintf(buffer, bufsize, "F:\\project\\net\\sock%d_header.log", iter->first);
			iter->second->achieve_header(buffer);
			_snprintf(buffer, bufsize, "F:\\project\\net\\sock%d_data.log", iter->first);
			iter->second->achieve_data(buffer);
		}
	} 
}
#else 
void CSelect::Dump(const SOCKET s){
}
void CSelect::Dump(const SOCKET s, HTTPPacket *){}
#endif 