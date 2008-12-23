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
	//	// ɾ��Ϊsocket����Ļ�����
		if (iter->second != NULL) 
			delete iter->second;
		// ɾ��socket
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
			// ������д��
			// ����İ����Ѿ��������ã���˱�����иı�
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

	// �洢����
	const int bytes_stored = peekMessage(lpBuffers->buf, bytes_read, s);
	if (bytes_stored == 0)
		return 0;


	// ��֤����
	HTTPPacket* packet = checkContent(s);
	if (NULL != packet) {
		Dump(s, packet);
		// ���ͨ����֤�������ݰ����뵽
		addCompletedPacket(s, packet);
		
	} else {
		return 0;
	}

	// ���ﲢ���޸Ļ�����
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

// ���SOCKET �Ƿ���Ҫ����
// ����Ѿ�������map������ôֱ�ӷ��ض�Ӧ��HTTPPacket
// ���� ����һ����������map����
// ע���������NULL, ����SOCKET����Ҫ����
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
	// ��һ���������.....
	if (s == NULL) return NULL;

	// ������Ѿ���ɣ�����֤����
	// ���ͨ���������������ȡ���������ض�Ӧָ��
	// ���δͨ���򷵻�NULL
	if (sock_data->isComplete()) {
		const int result_check =  checkData(sock_data, s);
		if (HttpContentChecker::CHECK_PASSED == result_check) {
			// ���ͨ��()
			HTTPPacket *packet = sock_data->detachNext();
			if (packet == NULL) {
				// �����������һ��������ô�Ƴ�socket****
				// ������Ƴ��ᣬ�´ν����ᴦ�������˱����Ƴ�
				_sockets_map_.erase(s);
			} else {
				_sockets_map_[s] = packet;
			}
			return sock_data;
		} else /*if (HttpContentChecker::CHECK_DENYED == result_check) */{
			// δͨ�����
			// ����һ������404�����������socket
			return NULL;
		}
	} else { // �������������
		return NULL;
	}
}

// �Ƿ���Ҫ����
bool CSelect::needStored(HTTPPacket *packet) {
	if (HttpContentChecker::needCheck(packet) 
			== HttpContentChecker::CHECK_NEEDLESS)
		return false;
	else 
		return true;
}

// �������ݰ�
// ������ݰ��Ƿ����������뱣֤����������
int CSelect::checkData(HTTPPacket *packet, const SOCKET s) {
	// �����ѧҪ�������������
	return HttpContentChecker::checkContent(packet);
}

// �˺���ȷ����SOCKET S���ܵ�����Ϣ�Ƿ���Ҫ��֤
// �����ѧҪ��֤��ֱ���ͷ�
// ������뵽�洢�ڣ����ڰ������Ժ������֤��
int CSelect::peekMessage(char *buf, const int len, const SOCKET s) {
	try {
		HTTPPacket* sock_data = createSOCKETPacket(s);
		if (sock_data == NULL) {
			// �����ֿ����ԣ�����ʧ�ܣ����߲�����Ҫ��
			return 0;
		} else {
			// �����ݴ���
			const int byte_stored = sock_data->addBuffer(buf, len);
			// ���򵥵������ж�
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

	// ���ң������զ��ɾ��
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

// �����Ƿ�ѧҪ����
// �����map����S��Ӧ��value == NULL,
// ��ô�Ͳ�ѧҪ����
int CSelect::needChecker(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.find(s);
	if (iter == _sockets_map_.end()) {		
		// δ��map���ҵ����ݣ� ��ôsocket��������δ֪��
		return SELECT_CHECK_UNKNOWN;
	} else if (iter->second == NULL) {
		// �����socket��Ӧ��ֵ��NULL, ��ôsocket����Ҫ����
		return SELECT_CHECK_NEEDLESS;
	} else {
		// ����ҵ��˰�����ôѧҪ����
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
	// ��ʼ�������� 
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