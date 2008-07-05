#include "StdAfx.h"
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
#include <utility\HttpContentChecker.h>
#include ".\globalcontrol.h"
#include ".\selectio.h"
#include "debug.h"

// Ŀǰ������
// 1. �ڴ�й©
// 2. ��chunk�Ĵ��� Ӧ��ֱ���ӵ�
// 3. SAVEDATA ��Ȼ���쳣

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
// �ڵ���WSPRecvʱʹ��
// ���������SOCKET ���ܴ����򷵻�1 
int CSelectIO::prerecv(SOCKET s, LPWSABUF lpBuffers, 
					   DWORD dwBufferCount, DWORD *recv_bytes) {
    using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	// ���û����ɵ�socket
	HTTPPacket * packet = getCompletedPacket(s);
	if (packet == NULL) {
		return 1; 
	}

	// ��֤���Ƿ�Ϸ���������Ϸ�, ��ɾ�����������
	// ���һ�����ɴ��
	//if ( false == checkWholePacket(packet)) {
	//	*recv_bytes = 0;
	//	removeCompletedPacket(s, packet); 
	//	DebugStringNoDres("****************************************");
	//	return 0;
	//} 

	// ��ȡһ��
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();
	// ���а����Ѿ�����
	if (raw_packet == NULL) {
		*recv_bytes = 0;
		// �Ƴ���
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

			if (bytes == 0) break;	// ����Ѿ��������
			*recv_bytes += bytes; 
		} 

		file.close();
		return 0;
	}
}

// ������ preselect
// ���������SPI�е�����һ���select֮ǰ����
// �������0�����ٵ���select,ֱ�ӷ���
int CSelectIO::preselect(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	if (readfds == NULL)
		return 1;

	// ���û���Ѿ���ɵ�IO
	if (isAnyCompleteSOCKET() == false) {
		return 1;
	}

	fd_set complete_readfds, new_readfds;
	FD_ZERO(&new_readfds);FD_ZERO(&complete_readfds);
	getAllCompleteSOCKET(&complete_readfds);

	// ���SOCKETͬʱ������complete_readfds��readfdsʱ
	// ���ǽ�������socket���뵽new_readfds;
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

// ��SPI�е�select���غ����
// ��������鿴readfds���Ƿ����ѧҪ�����IO
// ���ѧҪ��������еõ����ݲ����棬
// Ȼ�ִ�fd_set���Ƴ�(�����δ��ɴ���)
// ����Ѿ���ɴ��䣬�������뵽����ɵĶ�����
int CSelectIO::postselect(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	if (readfds == NULL)
		return 0;
	fd_set need_to_remove;
	FD_ZERO(&need_to_remove);

	for (int i = 0; i < readfds->fd_count; ++i) {
		// �����Ҫ����
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

			// �ڽ��������Ժ���ѧҪ�Ƴ�socket�Ӹ�����readfds
			FD_SET(s, &need_to_remove);
		}
	}

	FDSET_Del(readfds,  &need_to_remove);

	return 0;
}

/////////////////////////////////////////////
// �����Ƿ���Ϲ���
bool CSelectIO::checkWholePacket(HTTPPacket * packet) {
	HttpContentChecker * checker = HttpContentChecker::getChecker(packet->getHeader());
	return checker->checkHTTPContent(packet);
}
/////////////////////////////////////////////
// �������ڽ��ܵ�IO
HTTPPacket * CSelectIO::getSOCKETPacket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (_sockets_map_.end() == iter) {
		HTTPPacket *packet = new HTTPPacket();
		_sockets_map_.insert(std::make_pair(s, packet));
		return packet;
	}

	return iter->second;
} 

// �Ӱ��л�ȡ���ݲ�����
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	HTTPPacket* sock_data  = getSOCKETPacket(s);

	// д����ܵ��İ�
	char filename[1024];
	sprintf(filename, "c:\\recv\\%d_%d.log", s, len);
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
	file.write(buf, len);
	file.close();

	ODS("sock_data->addBuffer(buf, len);");
	int bytes_written = sock_data->addBuffer(buf, len);

	// �����ǰ���Ѿ���ɣ����map���Ƴ��������뵽��ɶ��е��� 
	// ���һЩ����������Լ����ҲӦ�÷�����ɶ���
	//    �磺HTTP�����ͣ� ��С�ȵ�.....
	if (sock_data->isComplete()) { 
		ODS("complete.....");
		// ���뵽��ɶ��е���
		addCompletedPacket(s, sock_data);

		// ������ɵİ�
		char filename[1024];
		sprintf(filename, "c:\\comdata\\%d.log", s, len);
		sock_data->achieve(filename);

		// �����һ�������ڣ������map,����ֱ��ɾ��
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

// ��֤��ӦSOCKET�İ��Ƿ�Ӧ�ñ��洢
// �������ǻ�鿴��ʱ�����SOCKET�����Ƿ����, ���������ѧҪ����
// ��������ʹ��PEEK_MESSAGE����recv, �鿴��Ӧ��SOCKET�ǲ���HTTPЭ�飬
//  ������򱣴棬�������
bool CSelectIO::needStored(const SOCKET s) {
	// �����Ӧ��s, ����Ĳ���NULL�� ��Ӧ�ñ�����
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

	// ��ȡǰ�ĸ��ֽڣ��鿴�Ƿ���'http', ���������򲻴���
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
 
	// ��������ĳ��Ȳ��� 
	if (recv_bytes < strlen("HTTP")) { // HTTP�ĳ���
		OutputDebugString("needcheck return false, too short");
		return false;
	}
	 
	// �����HTTP��ͷ
	buf[buf_size-1] = '\0';
	if ( buf == strstr(buf, HTTP_PACHET_HEADER)) {
		// ����ͷ��
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

// ɾ�������б������ʱ��
void CSelectIO::clearAllPackets() {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) 
		delete iter->second;
	}
	_sockets_map_.clear();
}

/////////////////////////////////////////////
// �����Ѿ���ɵ�IO

// �������Ѿ�����ɰ���socket�����fd_set����
// �˺���һ�����preselect�е���
void CSelectIO::getAllCompleteSOCKET(fd_set *readfds) {
	COMPLETED_PACKETS::const_iterator iter = completed_packets_.begin();
	while ( iter != completed_packets_.end()) {
		FD_SET(iter->first, readfds);
		iter = completed_packets_.upper_bound(iter->first);
	}
} 

// �鿴�Ƿ�����Ѿ���ɵİ�
bool CSelectIO::isAnyCompleteSOCKET() {
	return completed_packets_.size() != 0;
}

// �ͷ�������ɵİ�
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

// ����SOCKET��ӦHTTPPacket�İ���ӵ���ɶ��е���
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
			delete p;		// **** ��������ˣ������ڴ�й©
			completed_packets_.erase(iter);
			return 1;
		}
	}
	return 0; 
}

// ��ȡ��SOCKET��Ӧ��һ���Ѿ���ɵİ�
HTTPPacket * CSelectIO::getCompletedPacket(const SOCKET s) {
	COMPLETED_PACKETS::iterator iter = completed_packets_.lower_bound(s);
	if (completed_packets_.end() == iter) {
		return NULL;
	} else {
		return iter->second;
	}
}
