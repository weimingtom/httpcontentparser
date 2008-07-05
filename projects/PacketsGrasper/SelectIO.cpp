#include "StdAfx.h"
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
#include <utility\HttpContentChecker.h>
#include ".\globalcontrol.h"
#include ".\selectio.h"
#include "debug.h"

// 目前的问题
// 1. 内存泄漏
// 2. 对chunk的处理， 应该直接扔掉
// 3. SAVEDATA 仍然有异常

extern WSPPROC_TABLE	NextProcTable;	

CSelectIO::CSelectIO(void) {
}

CSelectIO::~CSelectIO(void) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	// freeAllCompletedPacket();
	clearAllPackets();
}


/////////////////////////////////////////////
// public members
// 在调用WSPRecv时使用
// 如果给定的SOCKET 不能处理则返回1 
int CSelectIO::prerecv(SOCKET s, LPWSABUF lpBuffers, 
					   DWORD dwBufferCount, DWORD *recv_bytes) {
    using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	// 如果没有完成的socket
	HTTPPacket * packet = getCompletedPacket(s);
	if (packet == NULL) {
		return 1; 
	}

	// 验证包是否合法，如果不合法, 则删除包，并填充
	// 填充一个不可达包
	//if ( false == checkWholePacket(packet)) {
	//	*recv_bytes = 0;
	//	removeCompletedPacket(s, packet); 
	//	DebugStringNoDres("****************************************");
	//	return 0;
	//} 

	// 获取一个
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();
	// 所有包都已经发送
	if (raw_packet == NULL) {
		*recv_bytes = 0;
		// 移除包
		removeCompletedPacket(s, packet);
		return 0; 
	} else {
		char filename[1024];
		sprintf(filename, "c:\\written\\%d_%d.log", s);
		std::fstream file;
		file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
		*recv_bytes = 0;
		for (int i = 0; i < dwBufferCount; i++) {
			DWORD bytes = raw_packet->read(lpBuffers[i].buf, lpBuffers[i].len);
			file.write(lpBuffers[i].buf, bytes);

			if (bytes == 0) break;	// 如果已经接受完毕
			*recv_bytes += bytes; 
		} 

		file.close();
		return 0;
	}
}

// 函数： preselect
// 这个函数在SPI中调用下一层的select之前调用
// 如果返回0，则不再调用select,直接返回
int CSelectIO::preselect(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	if (readfds == NULL)
		return 1;

	// 如果没有已经完成的IO
	if (isAnyCompleteSOCKET() == false) {
		return 1;
	}

	fd_set complete_readfds, new_readfds;
	FD_ZERO(&new_readfds);FD_ZERO(&complete_readfds);
	getAllCompleteSOCKET(&complete_readfds);

	// 如果SOCKET同时存在于complete_readfds和readfds时
	// 我们将这样的socket放入到new_readfds;
	for (int i = 0; i < complete_readfds.fd_count; ++i) {
		for (int j = 0; j < readfds->fd_count; ++j) {
			if (readfds->fd_array[j] == complete_readfds.fd_array[i]) {
				FD_SET(readfds->fd_array[j], &new_readfds);
			}
		}
	}

	if (new_readfds.fd_count > 0 ) {
		FD_ZERO(readfds);
		FDSET_Set(readfds, &new_readfds);
		return 0;
	} else { 
		return 1;
	}
}

// 在SPI中的select返回后调用
// 首先他会查看readfds中是否存在学要处理的IO
// 如果学要处理，则从中得到数据并保存，
// 然手从fd_set中移除(如果上未完成传输)
// 如果已经完成传输，则将他放入到已完成的队列中
int CSelectIO::postselect(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	if (readfds == NULL)
		return 0;
	fd_set need_to_remove;
	FD_ZERO(&need_to_remove);

	for (int i = 0; i < readfds->fd_count; ++i) {
		// 如果需要处理
		const SOCKET s = readfds->fd_array[i];
		if (true == needStored(s)) {
			const int buf_size = 1024 * 64;
			char buffer[buf_size];
			WSABUF wsabuf;		// buffer
			wsabuf.buf = buffer;
			wsabuf.len = buf_size;
			
			const DWORD buf_count = 1;
			INT errorno = 0;
			DWORD bytes_recv = 0, flags = 0;
			int ret = NextProcTable.lpWSPRecv(s, &wsabuf, 1, 
				&bytes_recv, &flags, NULL, NULL, NULL, &errorno);

			graspData(s, wsabuf.buf, bytes_recv);

			// 在接受数据以后我学要移除socket从给定的readfds
			FD_SET(s, &need_to_remove);
		}
	}

	FDSET_Del(readfds,  &need_to_remove);

	return 0;
}

/////////////////////////////////////////////
// 检查包是否符合规则
bool CSelectIO::checkWholePacket(HTTPPacket * packet) {
	HttpContentChecker * checker = HttpContentChecker::getChecker(packet->getHeader());
	return checker->checkHTTPContent(packet);
}
/////////////////////////////////////////////
// 处理正在接受的IO
HTTPPacket * CSelectIO::getSOCKETPacket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (_sockets_map_.end() == iter) {
		HTTPPacket *packet = new HTTPPacket();
		_sockets_map_.insert(std::make_pair(s, packet));
		return packet;
	}

	return iter->second;
} 

// 从包中获取数据并保存
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	HTTPPacket* sock_data  = getSOCKETPacket(s);

	// 写入接受到的包
	char filename[1024];
	sprintf(filename, "c:\\recv\\%d_%d.log", s, len);
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
	file.write(buf, len);
	file.close();

	ODS("sock_data->addBuffer(buf, len);");
	int bytes_written = sock_data->addBuffer(buf, len);

	// 如果当前包已经完成，则从map中移除，并放入到完成队列当中 
	// 如果一些条件不符合约束，也应该放入完成队列
	//    如：HTTP的类型， 大小等等.....
	if (sock_data->isComplete()) { 
		ODS("complete.....");
		// 放入到完成队列当中
		addCompletedPacket(s, sock_data);

		// 保存完成的包
		char filename[1024];
		sprintf(filename, "c:\\comdata\\%d.log", s, len);
		sock_data->achieve(filename);

		// 如果下一个包存在，则更新map,否则直接删除
		HTTPPacket * next_packet = sock_data->detachNext();
		if (next_packet == NULL) {
			SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
			if (iter != _sockets_map_.end()) 
				_sockets_map_.erase(iter);
		} else {
			_sockets_map_[s] = next_packet;
		}
	} 

	return bytes_written;
}

// 验证对应SOCKET的包是否应该被存储
// 首先我们会查看临时保存的SOCKET当中是否存在, 如果存在则学要保存
// 而后我们使用PEEK_MESSAGE调用recv, 查看对应的SOCKET是不是HTTP协议，
//  如果是则保存，否则放弃
bool CSelectIO::needStored(const SOCKET s) {
	// 如果对应的s, 保存的不是NULL， 则应该被处理
	SOCK_DATA_MAP::const_iterator iter = _sockets_map_.find(s);
	if (iter != _sockets_map_.end()) {
		char buffer[1024];
		sprintf(buffer, "needStored --- find SOCKET %d success!", s);
		OutputDebugString(buffer);
		return true; 
	} else {
		char buffer[1024];
		sprintf(buffer, "needStored --- find SOCKET %d failed!", s);
		OutputDebugString(buffer);
	}

	// 提取前四个字节，查看是否是'http', 不过不是则不处理
	const char HTTP_PACHET_HEADER[] = "HTTP";
	const int buf_size = 1024 * 64;
	char buf[buf_size] = {0};	
	WSABUF wsabuf;		// buffer
	wsabuf.buf = buf;
	wsabuf.len = buf_size-1;
	const DWORD buf_count = 1;
	INT errorno = 0;
	DWORD recv_bytes = 0, flags = MSG_PEEK;
	int ret = NextProcTable.lpWSPRecv(s, &wsabuf, 1, 
		&recv_bytes, &flags, NULL, NULL, NULL, &errorno);
	if (ret == SOCKET_ERROR) {
		OutputDebugString("needchecked...., peekmessage failed!");
		return false;
	}
 
	// 如果读出的长度不足 
	if (recv_bytes < strlen("HTTP")) { // HTTP的长度
		OutputDebugString("needcheck return false, too short");
		return false;
	}
	 
	// 如果以HTTP开头
	buf[buf_size-1] = '\0';
	if ( buf == strstr(buf, HTTP_PACHET_HEADER)) {
		// 解析头部
		HTTP_RESPONSE_HEADER header;
		header.parseHeader(buf, recv_bytes);
		const int type = header.getContentType();
		switch (type) {
			case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
			case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
			case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
				return true;
			default:
				return true;
		}
	} else {
		OutputDebugString("needcheck return false");
		return false;
	}
}

// 删除掉所有保存的临时包
void CSelectIO::clearAllPackets() {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) 
		delete iter->second;
	}
	_sockets_map_.clear();
}

/////////////////////////////////////////////
// 处理已经完成的IO

// 将所有已经有完成包的socket存放在fd_set当中
// 此函数一般会在preselect中调用
void CSelectIO::getAllCompleteSOCKET(fd_set *readfds) {
	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	while ( iter != completed_packets_.end()) {
		FD_SET(iter->first, readfds);
		iter = completed_packets_.upper_bound(iter->first);
	}
} 

// 查看是否存在已经完成的包
bool CSelectIO::isAnyCompleteSOCKET() {
	return completed_packets_.size() != 0;
}

// 释放所有完成的包
void CSelectIO::freeAllCompletedPacket() {
	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	for (; iter != completed_packets_.end(); ++iter) {
		char buffer[1024];
		sprintf(buffer, "c:\\%d.log", iter->first);
		iter->second->achieve(buffer);

		if (iter->second != NULL)
			delete iter->second;
	}
	completed_packets_.clear();
}

// 将与SOCKET对应HTTPPacket的包添加到完成队列当中
int CSelectIO::addCompletedPacket(const SOCKET s, HTTPPacket *p) {
	completed_packets_.insert(std::make_pair(s, p));
	return 0;
}
 
int CSelectIO::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	COMPLETED_PACKETS::iterator iter = completed_packets_.begin();
	COMPLETED_PACKETS::const_iterator iterEnd = completed_packets_.end();
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {

			DebugStringNoDres("prerecv ================================ remove packet");
			delete p;		// **** 把这个忘了，导致内存泄漏
			completed_packets_.erase(iter);
			return 1;
		}
	}
	return 0; 
}

// 获取与SOCKET对应第一个已经完成的包
HTTPPacket * CSelectIO::getCompletedPacket(const SOCKET s) {
	COMPLETED_PACKETS::iterator iter = completed_packets_.lower_bound(s);
	if (completed_packets_.end() == iter) {
		return NULL;
	} else {
		return iter->second;
	}
}
