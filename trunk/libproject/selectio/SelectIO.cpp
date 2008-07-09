#include "StdAfx.h"
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
#include <utility\HttpContentChecker.h>
#include ".\selectio.h"


int getBufferTotalSize(LPWSABUF lpBuffers, DWORD dwBufferCount) {
	int total_size = 0;
	for (int i = 0; i < dwBufferCount; ++i) {
		total_size += lpBuffers[i].len;
	}

	return total_size;
}

int WriteToBuffer(LPWSABUF	lpBuffers, DWORD dwBufferCount, 
				  const int begin, const char * data, const int len) {
  int address = 0;
  for (int i = 0; i < dwBufferCount; ++i) {
	  if (lpBuffers[i].len + address > begin)
		  break;
	  address += lpBuffers[i].len;
  }

  // ��������˱߽�
  if ( i == dwBufferCount )
	  return 0;

  address = begin - address; 
  // ��ʼ����
  int bytes_copyed = 0;
  for (; i < dwBufferCount; ++i) {
	  const int copyed = len - bytes_copyed > lpBuffers[i].len - address ? 
		  lpBuffers[i].len - address : len - bytes_copyed;
	  memcpy(&(lpBuffers[i].buf[address]), &(data[bytes_copyed]), copyed);
	  address = 0;
	  bytes_copyed += copyed;
  }	

  return bytes_copyed;
}

///////////////////////////////////////////////
//
CSelectIO::ContentCheckSetting::ContentCheckSetting() {
	checkImage_ = false;
	checkHTML_ = false;
	checkXML_  = false;
	minImageSize_ = 0;
	maxImageSize_ = 0x8fffffff;
}

void CSelectIO::ContentCheckSetting::setCheckHTML(const bool check) {
	checkHTML_ = check;
}
void CSelectIO::ContentCheckSetting::setCheckXML(const bool check) {
	minImageSize_ = check;
}
void CSelectIO::ContentCheckSetting::setCheckImage(const bool check) {
	checkImage_ = check;
}
void CSelectIO::ContentCheckSetting::setCheckImageSize(const int minsize, const int maxsize) {
	minImageSize_ = minsize;
	maxImageSize_ = maxsize;
}

bool CSelectIO::ContentCheckSetting::CheckContent(HTTP_RESPONSE_HEADER * header) {
	switch(header->getContentType()) {
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG: 
			return checkImage_;
		case HTTP_RESPONSE_HEADER::CONTYPE_HTML:
			return checkHTML_;
		default:
			return false;
	}
}
//========================================================
CSelectIO::CSelectIO() { 
	lpWSPRecv = NULL;
}

CSelectIO::~CSelectIO(void) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	freeAllCompletedPacket();
	clearAllPackets();
}

/////////////////////////////////////////////
// public members

void CSelectIO::setRecv(MYWSPRECV *recv) { 
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_); 
	lpWSPRecv = recv;
}
// �ڵ���WSPRecvʱʹ��
// ���������SOCKET ���ܴ����򷵻�1 
int CSelectIO::prerecv(SOCKET s, LPWSABUF lpBuffers, 
					   DWORD dwBufferCount, DWORD *recv_bytes) {
    using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	*recv_bytes = 0;
	assert (lpWSPRecv != NULL);
	// ����Ӧ�þ�������Ȼ������ڲ�д��
	// ���û����ɵ�socket
	const int TotalbufferSize = getBufferTotalSize(lpBuffers, dwBufferCount);

	HTTPPacket * packet = getCompletedPacket(s);
	if (packet == NULL) {
		return 1;
	}

	// ��֤���Ƿ�Ϸ���������Ϸ�, ��ɾ�����������
	// ���һ�����ɴ��
	//if ( packet->getHeader()->getContentType() == HTTP_RESPONSE_HEADER::CONTYPE_JPG) {
	//	removeCompletedPacket(s, packet);
	//	return 1;
	//} 

	// ��ȡһ��
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();


	// ���а����Ѿ�����
	if (raw_packet == NULL) {
		// �Ƴ���
		removeCompletedPacket(s, packet);
		return 0;
	} else {
		for (int i = 0; i < dwBufferCount; ++i) {
			const DWORD bytes = raw_packet->read(lpBuffers[i].buf, lpBuffers[i].len);
			*recv_bytes += bytes;
			if (bytes == 0 || raw_packet->getBytesCanRead() == 0) {
				removeCompletedPacket(s, packet);
			}
		}
	}

	if (*recv_bytes == 0) {
		return 1;
	} else {
		return 0;
	}

}

// ������ preselect
// ���������SPI�е�����һ���select֮ǰ����
// �������0�����ٵ���select,ֱ�ӷ���
int CSelectIO::preselect(fd_set *readfds) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	assert( lpWSPRecv != NULL);

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

	assert( lpWSPRecv != NULL);
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

			int ret = (*lpWSPRecv)(s, &wsabuf, 1, 
				&bytes_recv, &flags, NULL, NULL, NULL, &errorno);

			int completed = graspData(s, wsabuf.buf, bytes_recv);

			// �ڽ��������Ժ���ѧҪ�Ƴ�socket�Ӹ�����readfds
			// ��һ��Ҫ�Ƴ����� ��ʱ���յ��ľ��������İ���������
			// ���graspData�������һ�������İ��� �򷵻�0
			// �������1��������һ�������İ�����ô�Ͳ���Ҫ���뵽
			// need_to_remove����
			if (completed == 1)
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
	SOCK_DATA_MAP::iterator iter = _sockets_map_.lower_bound(s);
	SOCK_DATA_MAP::iterator iterEnd = _sockets_map_.upper_bound(s);
	for (; iter != iterEnd; ++iter) {
		if (iter->second->isComplete() == false) {
			return iter->second;
		} 
	} 

	HTTPPacket *packet = new HTTPPacket;
	_sockets_map_.insert(std::make_pair(s, packet));
	return packet;	
} 

// �Ӱ��л�ȡ���ݲ�����
// ����0������һ�������İ�
// ����1������һ�������İ�
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	try {
		bool completed_generated = false;
		int total_size = 0;
		while (total_size < len) {
			HTTPPacket* sock_data  = getSOCKETPacket(s);

			assert(sock_data->isComplete() == false);
			const int bytes_written = sock_data->addBuffer(buf, len);
			total_size += bytes_written;

			// �����ǰ���Ѿ���ɣ����map���Ƴ��������뵽��ɶ��е��� 
			// ���һЩ����������Լ����ҲӦ�÷�����ɶ���
			//    �磺HTTP�����ͣ� ��С�ȵ�.....
			if (sock_data->isComplete()) { 
				OutputDebugString("complete.....");
				// ���뵽��ɶ��е���
				addCompletedPacket(s, sock_data);				
				removePacket(s, sock_data);

				completed_generated = true;
			}
		} // while

		// ����������İ�����0�����򷵻�1
		if (completed_generated)
			return 0;
		else
			return 1;
	} catch (...) {
		return 1;
	}
}

bool CSelectIO::isThereUncompletePacket(const SOCKET s) {
	return _sockets_map_.find(s) != _sockets_map_.end();
}
// ��֤��ӦSOCKET�İ��Ƿ�Ӧ�ñ��洢
// �������ǻ�鿴��ʱ�����SOCKET�����Ƿ����, ���������ѧҪ����
// ��������ʹ��PEEK_MESSAGE����recv, �鿴��Ӧ��SOCKET�ǲ���HTTPЭ�飬
//  ������򱣴棬�������
bool CSelectIO::needStored(const SOCKET s) {
	// SOCKET s�Ƿ�����������İ������������ֱ�ӷ���true, ����������´���
	if (isThereUncompletePacket(s)) {
		OutputDebugString("isThereUncompletePacket(s) == true");
		return true;
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
	int ret = lpWSPRecv(s, &wsabuf, 1, 
		&recv_bytes, &flags, NULL, NULL, NULL, &errorno);
	if (ret == SOCKET_ERROR) {
		return false;
	}

	// �򽫴˰���������ɵİ���
	if (recv_bytes == 0) {
		OutputDebugString("brecv_bytes == 0");
	}
	// ��������ĳ��Ȳ��� 
	if (recv_bytes < strlen("HTTP")) { // HTTP�ĳ���
		return false;
	}
	 
	// �����HTTP��ͷ
	// ���ܲ�����ͷ�����Ǻ�
	buf[buf_size-1] = '\0';
	if ( buf == strstr(buf, HTTP_PACHET_HEADER)) {
		// ����ͷ��
		HTTP_RESPONSE_HEADER header;
		int result = header.parseHeader(buf, recv_bytes);
		if (result != 0) {
			return true;
		} else { // �ⲻ��һ��HTTP��
			return false;
		}
	} else {
		OutputDebugString("======not begin with HTTP=========");
		return false;
	}
}

// ɾ�������б������ʱ��
void CSelectIO::clearAllPackets() {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) {
			char buffer[1024];
			sprintf(buffer, "c:\\%d.log", iter->first);
			iter->second->achieve(buffer);
			delete iter->second;
		}
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
		if (iter->second != NULL) {
			delete iter->second;
		}
	}
	completed_packets_.clear();
}

// ����SOCKET��ӦHTTPPacket�İ���ӵ���ɶ��е���
int CSelectIO::addCompletedPacket(const SOCKET s, HTTPPacket *p) {
	completed_packets_.insert(std::make_pair(s, p));
	return 0;
}
 
int CSelectIO::removePacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	SOCK_DATA_MAP::const_iterator iterEnd = _sockets_map_.end();
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
			_sockets_map_.erase(iter);
			return 1;
		}
	}
	return 0; 
}

int CSelectIO::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	COMPLETED_PACKETS::iterator iter = completed_packets_.begin();
	COMPLETED_PACKETS::const_iterator iterEnd = completed_packets_.end();
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
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
