#include "StdAfx.h"
#include ".\selectio.h"
#include "httpcontentcheck.h"
#include "buffercallCOM.h"
#include <webcontenttype.h>
#include <logdebug.h>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>


const char * HTTP404_PACKET = "HTTP/1.1 404 Not Found\r\n\r\n";

////////////////////////////////////////////////
int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount) {
	int total_size = 0;
	for (int i = 0; i < static_cast<int>(dwBufferCount); ++i) {
		total_size += lpBuffers[i].len;
	}

	return total_size;
}

int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len) {
  int address = 0;
  int i;
  for (i = 0; i < static_cast<int>(dwBufferCount); ++i) {
	  if (static_cast<int>(lpBuffers[i].len + address) > begin)
		  break;
	  address += lpBuffers[i].len;
  }

  // 如果超出了边界
  if ( i == dwBufferCount )
	  return 0;

  address = begin - address; 
  // 开始拷贝
  int bytes_copyed = 0;
  for (; i < static_cast<int>(dwBufferCount); ++i) {
	  const int copyed = len - bytes_copyed > static_cast<int>(lpBuffers[i].len - address) ? 
		  lpBuffers[i].len - address : len - bytes_copyed;
	  memcpy(&(lpBuffers[i].buf[address]), &(data[bytes_copyed]), copyed);
	  address = 0;
	  bytes_copyed += copyed;
  }	

  return bytes_copyed;
}

//========================================================
CSelectIO::CSelectIO() { 
	lpWSPRecv = NULL;
}

CSelectIO::~CSelectIO(void) {
	socketPackets_.freeAllCompletedPacket();
	socketPackets_.clearAllPackets();
	// packet_handle_queue_.finialize();
}

void CSelectIO::finalize() {
	website_recorder_.saveWebsites();
}
/////////////////////////////////////////////
// public members


void CSelectIO::setRecv(MYWSPRECV *recv) { 
	lpWSPRecv = recv;

	// 初始化
	website_recorder_.initialize();
}
// 在调用WSPRecv时使用
// 如果给定的SOCKET 不能处理则返回1 
// 如果返回-1表示有错
int CSelectIO::prerecv(SOCKET s, LPWSABUF lpBuffers, 
					   DWORD dwBufferCount, DWORD *recv_bytes) {

	*recv_bytes = 0;
	assert (lpWSPRecv != NULL);
	// 这里应该尽量多的先缓冲区内部写入
	// 如果没有完成的socket
	const int TotalbufferSize = getBufferTotalSize(lpBuffers, dwBufferCount);

	HTTPPacket * packet = socketPackets_.getCompletedPacket(s);
	if (packet == NULL) {
		return 1;
	}

	int result;
	if (!packet_handle_queue_.getResult(packet, &result)) {
		return 1;
	}
	// 检查内容
	// 如果检查失败
	
	if (CONTENT_CHECK_PORN == result) {
		website_recorder_.updateWebsites(dnsmap_.get(s), CONTENT_CHECK_PORN);
		socketPackets_.removeCompletedPacket(s, packet);
		*recv_bytes = 0;
		return 0;
		// 应该替换包
		//HTTPPacket *new_packet = new HTTPPacket;
		//FillBlankPacket(packet, new_packet);
		//socketPackets_.replacePacket(s, packet, new_packet);
		//delete packet;
		//packet = new_packet;
	} else {
		website_recorder_.updateWebsites(dnsmap_.get(s), CONTENT_CHECK_NORMAL);
	}
	
	// 获取一个
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();
	assert(raw_packet != NULL);

	if (raw_packet->getBytesCanRead() == 0) {
		*recv_bytes = 0;
		packet_handle_queue_.removeCompletePacket(packet);
		socketPackets_.removeCompletedPacket(s, packet);
	}

	//char data[1024];
	//sprintf(data, "totalbuf size: %d", TotalbufferSize);
	//OutputDebugString(data);

	// 所有包都已经发送
	// 如果收到长度为0的包呢
	if (packet->transfefTail() && raw_packet->getBytesCanRead() == 0) {
		*recv_bytes = 0;
	} else {
		for (int i = 0; i < static_cast<int>(dwBufferCount); ++i) {
			const DWORD bytes = raw_packet->read(lpBuffers[i].buf, lpBuffers[i].len);
		
			*recv_bytes += bytes;
			if (bytes == 0 || raw_packet->getBytesCanRead() == 0) {
				if (packet->transfefTail() == false)
					socketPackets_.removeCompletedPacket(s, packet);
			}
		}

		assert (*recv_bytes != 0);
	}
	
	return 0;
}

// 函数： preselect
// 这个函数在SPI中调用下一层的select之前调用
// 如果返回0，则不再调用select,直接返回
int CSelectIO::preselect(fd_set *readfds) {
	assert( lpWSPRecv != NULL);

	if (readfds == NULL)
		return 1;

	// 如果没有已经完成的IO
	if (socketPackets_.isAnyCompleteSOCKET() == false) {
		return 1;
	}

	fd_set complete_readfds, new_readfds;
	FD_ZERO(&new_readfds);FD_ZERO(&complete_readfds);
	socketPackets_.getAllCompleteSOCKET(&complete_readfds);

	// 如果SOCKET同时存在于complete_readfds和readfds时
	// 我们将这样的socket放入到new_readfds;
	for (int i = 0; i < static_cast<int>(complete_readfds.fd_count); ++i) {
		for (int j = 0; j < static_cast<int>(readfds->fd_count); ++j) {
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
	assert( lpWSPRecv != NULL);
	if (readfds == NULL)
		return 0;
	fd_set need_to_remove;
	FD_ZERO(&need_to_remove);

	for (int i = 0; i < static_cast<int>(readfds->fd_count); ++i) {
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

			int ret = (*lpWSPRecv)(s, &wsabuf, 1, 
				&bytes_recv, &flags, NULL, NULL, NULL, &errorno);

			int completed = graspData(s, wsabuf.buf, bytes_recv);

			// 在接受数据以后我学要移除socket从给定的readfds
			// 不一定要移除啊， 有时候收到的就是完整的包啊！！！
			// 如果graspData处理的是一个完整的包， 则返回0
			// 如果返回1，代表不是一个完整的包，那么就不需要放入到
			// need_to_remove当中
			if (completed == 1)
				FD_SET(s, &need_to_remove);
		}
	}

	FDSET_Del(readfds,  &need_to_remove);

	return 0;
}

/////////////////////////////////////////////
// 处理正在接受的IO

// 从包中获取数据并保存
// 返回0代表是一个完整的包
// 返回1代表不是一个完整的包
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	try { 
		bool completed_generated = false; 
		int total_size = 0; 

		// 获取相关的包
		HTTPPacket* sock_data  = socketPackets_.getSOCKETPacket(s);
		assert( sock_data != NULL);

		//char filename[1024];
		//sprintf(filename, "d:\\debuglog\\s%d_%d.log",  s, sock_data->getCode());
		//OutputDebugString(filename);
		//WriteRawData(filename, buf, len);

		// 如果接收到了长度为0
		if (len == 0) {
			// 将包表示为完整的
			int added_length;
			const int result = sock_data->addBuffer(buf, len, &added_length);
			if (0 != result) {
				char buffer[1024];
				sprintf(buffer, "1. SOCKET %d, Packet Code %d", s, sock_data->getCode());
				OutputDebugString(buffer);
			}

			// 如果出现了错误
			assert ( added_length == result);
			socketPackets_.removePacket(s, sock_data);
	 		socketPackets_.addCompletedPacket(s, sock_data);
			packet_handle_queue_.addPacket(sock_data);
			completed_generated = true;
		} else {
			// 由于这里可能出现头部，所以在这里也应该进行头部验证啊....
			// 但是这里是已经接收到的包，所以受到了必须将它直接送上去，不能放弃
			int bytes_written;
			const int result = sock_data->addBuffer(&(buf[total_size]), len - total_size, &bytes_written);
			total_size += bytes_written;

			//// 出现了问题
			//if (0 != result) {
			//	char buffer[1024];
			//	sprintf(buffer, "2. SOCKET %d, Packet Code %d", s, sock_data->getCode());
			//	OutputDebugString(buffer);
			//}


			// 如果当前包已经完成，则从map中移除，并放入到完成队列当中 
			// 如果一些条件不符合约束，也应该放入完成队列
			//    如：HTTP的类型， 大小等等.....
			if (sock_data->isComplete() || result != 0) { 
				// 放入到完成队列当中
				socketPackets_.removePacket(s, sock_data);
				socketPackets_.addCompletedPacket(s, sock_data);
				packet_handle_queue_.addPacket(sock_data);
				completed_generated = true;
			}

		}

		// 如果有完整的包返回0，否则返回1
		if (completed_generated)
			return 0;
		else
			return 1;
	} catch (...) {
		return 1;
	}
}

// 验证对应SOCKET的包是否应该被存储
// 首先我们会查看临时保存的SOCKET当中是否存在, 如果存在则学要保存
// 而后我们使用PEEK_MESSAGE调用recv, 查看对应的SOCKET是不是HTTP协议，
//  如果是则保存，否则放弃
bool CSelectIO::needStored(const SOCKET s) {
	// SOCKET s是否包含不完整的包，如果包含则直接返回true, 否则继续向下处理
	if (socketPackets_.isThereUncompletePacket(s)) {
		return true;
	}

	// 如果存在于白名单当中
	if (checkWhiteDNS(s)) {
		return false;
	}


	// 提取前四个字节，查看是否是'http', 不过不是则不处理
	const char HTTP_PACHET_HEADER[] = "HTTP";
	const int buf_size = 1024;
	char buf[buf_size] = {0};	
	WSABUF wsabuf;		// buffer
	wsabuf.buf = buf;
	wsabuf.len = buf_size-1;
	const DWORD buf_count = 1;
	INT errorno = 0;
	DWORD recv_bytes = 0, flags = MSG_PEEK;
	int ret = lpWSPRecv(s, &wsabuf, 1, 
		&recv_bytes, &flags, NULL, NULL, NULL, &errorno);
	if (ret == SOCKET_ERROR) {
		return false;
	}

	// 如果读出的长度不足 
	if (recv_bytes < strlen("HTTP")) { // HTTP的长度
		return false;
	}
	 
	// 如果以HTTP开头
	// 可能不包含头部，呵呵
	buf[buf_size-1] = '\0';
	const char * header = strstr(buf, HTTP_PACHET_HEADER);
	if ( header == buf ) {
		// 解析头部
		HTTP_RESPONSE_HEADER header;
		int result = header.parseHeader(buf, recv_bytes);
		if (result == 0) {
			return false;
		}
		
		// we should check the content here, we just store the 
		// XML, BMP, JEPG, PNG, HTML
		// all other things we should pass it without storing.
		if (isImage(header.getContentType()) || isText(header.getContentType())) {
			return true;
		} else {
			return false;
		}
	} else {
		// 如果不是以HTTP开头 
		// 注意：在开始的时候我们已经处理了可能是一个HTTP协议部分的情况
		return false;
	}
}

bool checkDNS(const std::string &dns) {
	AutoInitInScale _auto_com_init;
	try {
		_VARIANT_BOOL passed;

		// create Instance
		IDNSSetting *dnssetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_DNSSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&dnssetting);
		if (FAILED(hr)) {
			return FALSE;
		}

		// 检测是否是白名单
		VARIANT_BOOL enabled;
		dnssetting->isWhiteDNS(_bstr_t(dns.c_str()), &enabled);
		dnssetting->Release();
		return convert(enabled);
		CoUninitialize();
	} catch (_com_error &) {
		return false;
	}
}

bool CSelectIO::checkWhiteDNS(SOCKET s) {
	std::string dns = dnsmap_.get(s);
	if (dns == "")
		return false;

	return checkDNS(dns);
}

void CSelectIO::removeDNSMap(SOCKET s) {
	dnsmap_.remove(s);
}

void CSelectIO::addDNS(SOCKET s, const std::string &addr) {
	dnsmap_.add(s, addr);
}




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
void SocketPackets::getAllCompleteSOCKET(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	while ( iter != completed_packets_.end()) {
		FD_SET(iter->first, readfds);
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
int SocketPackets::replacePacket(SOCKET s, HTTPPacket *p, HTTPPacket * new_packet) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DATA_MAP::iterator iter = _sockets_map_.lower_bound(s);
	SOCK_DATA_MAP::const_iterator iterEnd = _sockets_map_.upper_bound(s);
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
			assert(s == iter->first);
			iter->second = new_packet;
			return 1;
		}
	}

	return 0;
}
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
