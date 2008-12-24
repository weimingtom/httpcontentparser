#include "StdAfx.h"
#include ".\selectio.h"
#include "httpcontentcheck.h"
#include "buffercallCOM.h"
#include <webcontenttype.h>
#include <logdebug.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>


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

  // ��������˱߽�
  if ( i == dwBufferCount )
	  return 0;

  address = begin - address; 
  // ��ʼ����
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
	// �������
	// ������ʧ��
	OutputDebugString("=======================handler select...");
	if (false == handlePacket(packet)) {
		removeCompletedPacket(s, packet);
		return 1;
	}
	
	// ��ȡһ��
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();
	assert(raw_packet != NULL);

	if (raw_packet->getBytesCanRead() == 0) {
		*recv_bytes = 0;
		removeCompletedPacket(s, packet);
	}

	//char data[1024];
	//sprintf(data, "totalbuf size: %d", TotalbufferSize);
	//OutputDebugString(data);

	// ���а����Ѿ�����
	for (int i = 0; i < static_cast<int>(dwBufferCount); ++i) {
		const DWORD bytes = raw_packet->read(lpBuffers[i].buf, lpBuffers[i].len);

		//char filename[1024];
		//sprintf(filename, "E:\\workspace\\debuglog\\%d_%dw.log", packet->getCode(), s);
		//WriteRawData(filename, lpBuffers[i].buf, bytes);

		*recv_bytes += bytes;
		if (bytes == 0 || raw_packet->getBytesCanRead() == 0) {
			removeCompletedPacket(s, packet);
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

// ��SPI�е�select���غ����
// ��������鿴readfds���Ƿ����ѧҪ������IO
// ���ѧҪ����������еõ����ݲ����棬
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

	for (int i = 0; i < static_cast<int>(readfds->fd_count); ++i) {
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
			// ���graspData��������һ�������İ��� �򷵻�0
			// �������1����������һ�������İ�����ô�Ͳ���Ҫ���뵽
			// need_to_remove����
			if (completed == 1)
				FD_SET(s, &need_to_remove);
		}
	}

	FDSET_Del(readfds,  &need_to_remove);

	return 0;
}

/////////////////////////////////////////////
// �������ڽ��ܵ�IO

// �Ӱ��л�ȡ���ݲ�����
// ����0������һ�������İ�
// ����1��������һ�������İ�
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	try {
		bool completed_generated = false; 
		int total_size = 0; 

		// ��ȡ��صİ�
		HTTPPacket* sock_data  = getSOCKETPacket(s);
		assert( sock_data != NULL);

		//char filename[1024];
		//sprintf(filename, "E:\\workspace\\debuglog\\%d_%d.log", sock_data->getCode(), s);
		//WriteRawData(filename, buf, len);


		bool store_to_log = false;
		// ������յ��˳���Ϊ0
		if (len == 0) {
			// ������ʾΪ������
			int added_length;
			const int result = sock_data->addBuffer(buf, len, &added_length);

			// ��������˴���
			if (0 != result) {
				store_to_log = true;
			}

			assert ( added_length == result);
			removePacket(s, sock_data);
			addCompletedPacket(s, sock_data);				
			completed_generated = true;

			// �����н���
			//char buffer[1024];			
			//sprintf(buffer, "%d finished with 0 tail", sock_data->getCode());
			//OutputDebugString(buffer);

			//sprintf(buffer, "E:\\workspace\\debuglog\\0recv%d.log", s);
			//sock_data->achieve(buffer);
		} else {
			while (total_size < len) {
				// ����������ܳ���ͷ��������������ҲӦ�ý���ͷ����֤��....
				// �����������Ѿ����յ��İ��������ܵ��˱��뽫��ֱ������ȥ�����ܷ���
				int bytes_written;
				const int result = sock_data->addBuffer(&(buf[total_size]), len - total_size, &bytes_written);
				total_size += bytes_written;

				// ��������˴���
				if (0 != result) {
					store_to_log = true;
				}

				// �����ǰ���Ѿ���ɣ����map���Ƴ��������뵽��ɶ��е��� 
				// ���һЩ����������Լ����ҲӦ�÷�����ɶ���
				//    �磺HTTP�����ͣ� ��С�ȵ�.....
				if (sock_data->isComplete()) { 
					// ���뵽��ɶ��е���
					
					removePacket(s, sock_data);
					addCompletedPacket(s, sock_data);
					completed_generated = true;

					// achieve
					//char buffer[200];
					//sprintf(buffer, "%d finished=", sock_data->getCode());
					//OutputDebugString(buffer);

					// ����������Ƴ��ˣ� ѧҪ������һ����
					// �����������������߸ĳ�<=, ��ô��һ��HTTP�����������һ����HTTP��ʱ������ִ���
					if (total_size < len) {
						sock_data  = getSOCKETPacket(s);
					}
				}

				if (bytes_written == 0) {
					//assert(false);
					break;
				}
			} // while
		}

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
		return true;
	}

	// ��ȡǰ�ĸ��ֽڣ��鿴�Ƿ���'http', ���������򲻴���
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

	// ��������ĳ��Ȳ��� 
	if (recv_bytes < strlen("HTTP")) { // HTTP�ĳ���
		return false;
	}
	 
	// �����HTTP��ͷ
	// ���ܲ�����ͷ�����Ǻ�
	buf[buf_size-1] = '\0';
	const char * header = strstr(buf, HTTP_PACHET_HEADER);
	if ( header == buf ) {
		// ����ͷ��
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
		// ���������HTTP��ͷ 
		// ע�⣺�ڿ�ʼ��ʱ�������Ѿ������˿�����һ��HTTPЭ�鲿�ֵ����
		return false;
	}
}

// ɾ�������б������ʱ��
void CSelectIO::clearAllPackets() {
	char buffer[1024];
	SOCK_DATA_MAP::iterator iter = _sockets_map_.begin();
	for (; iter != _sockets_map_.end(); ++iter) {
		if (iter->second != NULL) {
			sprintf(buffer, "E:\\workspace\\debuglog\\uncomplete\\%d.txt", iter->second->getCode());
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
			removeBufferResult(iter->second);	// �Ƴ������¼
			delete iter->second;
		}
	}
	completed_packets_.clear();
}

int CSelectIO::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// OutputDebugString("remove complete socket");
	COMPLETED_PACKETS::iterator iter = completed_packets_.begin();
	COMPLETED_PACKETS::const_iterator iterEnd = completed_packets_.end();
	for (; iter != iterEnd; ++iter) {
		if (iter->second->getCode() == p->getCode()) {
			removeBufferResult(p);

			delete p;		// **** ��������ˣ������ڴ�й©
			completed_packets_.erase(iter);
			return 1;
		}
	}
	return 0; 
}


// ��ȡ��SOCKET��Ӧ��һ���Ѿ���ɵİ�
HTTPPacket * CSelectIO::getCompletedPacket(const SOCKET s) {
	COMPLETED_PACKETS::iterator iter = completed_packets_.find(s);
	if (completed_packets_.end() == iter) {
		return NULL;
	} else {
		return iter->second;
	}
}

// ����SOCKET��ӦHTTPPacket�İ����ӵ���ɶ��е���
int CSelectIO::addCompletedPacket(const SOCKET s, HTTPPacket *p) {
	completed_packets_.insert(std::make_pair(s, p));
	return 0;
}

HTTPPacket * CSelectIO::getSOCKETPacket(const SOCKET s) {
	SOCK_DATA_MAP::iterator iter = _sockets_map_.lower_bound(s);
	SOCK_DATA_MAP::iterator iterEnd = _sockets_map_.upper_bound(s);
	for (; iter != iterEnd; ++iter) {
		assert (iter->second->isComplete() == false);
		return iter->second;
	}
	
	HTTPPacket *packet = new HTTPPacket;
	_sockets_map_.insert(std::make_pair(s, packet));

	return packet;	
}
 
int CSelectIO::removePacket(const SOCKET s, HTTPPacket *p) {
	OutputDebugString("removeBufferResult");
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



// �˺����������������
// 1. ���������Ƿ����԰������е���վ
// 2. ������������, ��ȷ���ð��Ƿ�Ӧ�ñ����
// 3. ��������������
bool CSelectIO::handlePacket(HTTPPacket *packet) {
	OutputDebugString("handle packet...");

	int result;
	// ���Ȳ����Ƿ��Ѿ�����������
	BUFFER_RESULT::iterator iter = content_check_result_.find(packet->getCode());
	if (content_check_result_.end() == iter) {
		result =  handler_.handleContent(packet);
		content_check_result_[packet->getCode()] = result;	// ������
	} else {
		result = iter->second;	// ֱ�ӷ��ؽ��
	}

	if (CONTENT_CHECK_PORN == result) {
		return false;
	} else {
		return true;
	}
}

void CSelectIO::removeBufferResult(HTTPPacket *packet) {
		BUFFER_RESULT::iterator iter = content_check_result_.find(packet->getCode());
		if (content_check_result_.end() != iter) {
			content_check_result_.erase(iter);
		} else {
			// assert(false);	
		}
	}