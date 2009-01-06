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
}

void CSelectIO::finalize() {
	packet_handle_queue_.finialize();
	website_recorder_.saveWebsites();
}
/////////////////////////////////////////////
// public members
void CSelectIO::setRecv(MYWSPRECV *recv) { 
	lpWSPRecv = recv;

	// ��ʼ��
	packet_handle_queue_.initialize();
	website_recorder_.initialize();
}
// �ڵ���WSPRecvʱʹ��
// ���������SOCKET ���ܴ����򷵻�1 
// �������-1��ʾ�д�
int CSelectIO::prerecv(SOCKET s, LPWSABUF lpBuffers, 
					   DWORD dwBufferCount, DWORD *recv_bytes) {

	*recv_bytes = 0;
	assert (lpWSPRecv != NULL);
	// ����Ӧ�þ�������Ȼ������ڲ�д��
	// ���û����ɵ�socket
	const int TotalbufferSize = getBufferTotalSize(lpBuffers, dwBufferCount);

	HTTPPacket * packet = packet_handle_queue_.getCompletedPacket(s);
	if (packet == NULL) {
		return 1;
	}

	int result;
	bool succ = packet_handle_queue_.getResult(packet, &result);
	// assert (succ);
	if (!succ) {
		return 1;
	}
	// �������
	// ������ʧ��
	
	if (CONTENT_CHECK_PORN == result) {
		// Ӧ���滻��, ֮ǰ�ķ�����ʹ��һ��ͼƬ�����
		//HTTPPacket *new_packet = new HTTPPacket;
		//FillBlankPacket(packet, new_packet);
		//socketPackets_.replacePacket(s, packet, new_packet);
		//delete packet;
		//packet = new_packet;
		website_recorder_.updateWebsites(dnsmap_.get(s), CONTENT_CHECK_PORN);
		packet_handle_queue_.removeCompletedPacket(s, packet);
		*recv_bytes = 0;
		return 0;
	} else {
		website_recorder_.updateWebsites(dnsmap_.get(s), CONTENT_CHECK_NORMAL);
	}
	
	// ��ȡһ��
	ProtocolPacket<HTTP_PACKET_SIZE> * raw_packet= packet->getRawPacket();
	assert(raw_packet != NULL);

	if (raw_packet->getBytesCanRead() == 0) {
		*recv_bytes = 0;
		packet_handle_queue_.removeCompletedPacket(s, packet);
	}

	// ���а����Ѿ�����
	// ����յ�����Ϊ0�İ���
	if (packet->transfefTail() && raw_packet->getBytesCanRead() == 0) {
		*recv_bytes = 0;
	} else {
		for (int i = 0; i < static_cast<int>(dwBufferCount); ++i) {
			const DWORD bytes = raw_packet->read(lpBuffers[i].buf, lpBuffers[i].len);
		
			*recv_bytes += bytes;
			if (bytes == 0 || raw_packet->getBytesCanRead() == 0) {
				if (packet->transfefTail() == false) {
					char filename[1024];
					sprintf(filename, "d:\\debuglog\\up\\%d.log",  s);
					packet->achieve(filename);

					sprintf(filename, "recv upward : %d", s);
					OutputDebugString(filename);

					packet_handle_queue_.removeCompletedPacket(s, packet);
				}
			}
		}

		assert (*recv_bytes != 0);
	}
	
	return 0;
}

// ������ preselect
// ���������SPI�е�����һ���select֮ǰ����
// �������0�����ٵ���select,ֱ�ӷ���
int CSelectIO::preselect(fd_set *readfds) {
	assert( lpWSPRecv != NULL);

	if (readfds == NULL)
		return 1;

	fd_set complete_readfds, new_readfds;
	FD_ZERO(&new_readfds);
	FD_ZERO(&complete_readfds);

	packet_handle_queue_.getAllCompleteSOCKET(&complete_readfds);

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
// ��������鿴readfds���Ƿ����ѧҪ�����IO
// ���ѧҪ��������еõ����ݲ����棬
// Ȼ�ִ�fd_set���Ƴ�(�����δ��ɴ���)
// ����Ѿ���ɴ��䣬�������뵽����ɵĶ�����
int CSelectIO::postselect(fd_set *readfds) {
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
// �������ڽ��ܵ�IO

// �Ӱ��л�ȡ���ݲ�����
// ����0������һ�������İ�
// ����1������һ�������İ�
int CSelectIO::graspData(const SOCKET s, char *buf, const int len) {
	try { 
		bool completed_generated = false; 
		int total_size = 0; 

		// ��ȡ��صİ�
		HTTPPacket* sock_data  = packet_handle_queue_.getSOCKETPacket(s);
		assert( sock_data != NULL);

		char filename[1024];
		sprintf(filename, "d:\\debuglog\\s%d.log",  s);
		WriteRawData(filename, buf, len);

		// ������յ��˳���Ϊ0
		//if (len == 0) {
		//	// ������ʾΪ������
		//	int added_length;
		//	const int result = sock_data->addBuffer(buf, len, &added_length);
		//	if (0 != result) {
		//		char buffer[1024];
		//		sprintf(buffer, "1. SOCKET %d, Packet Code %d", s, sock_data->getCode());
		//		OutputDebugString(buffer);
		//	}
		//	// ��������˴���
		//	assert ( added_length == result);
		//	packet_handle_queue_.packetIntact(s, sock_data);
		//	completed_generated = true;
		//} else {
		// ����������ܳ���ͷ��������������ҲӦ�ý���ͷ����֤��....
		// �����������Ѿ����յ��İ��������ܵ��˱��뽫��ֱ������ȥ�����ܷ���
		int bytes_written;
		const int result = sock_data->addBuffer(&(buf[total_size]), len - total_size, &bytes_written);
		total_size += bytes_written;

		//// ����������
		//if (0 != result) {
		//	char buffer[1024];
		//	sprintf(buffer, "2. SOCKET %d, Packet Code %d", s, sock_data->getCode());
		//	OutputDebugString(buffer);
		//}


		// �����ǰ���Ѿ���ɣ����map���Ƴ��������뵽��ɶ��е��� 
		// ���һЩ����������Լ����ҲӦ�÷�����ɶ���
		//    �磺HTTP�����ͣ� ��С�ȵ�.....
		if (sock_data->isComplete() /*|| result != 0*/) { 
			// ���뵽��ɶ��е���
			packet_handle_queue_.packetIntact(s, sock_data);
			completed_generated = true;
		}
		//}

		// ����������İ�����0�����򷵻�1
		if (completed_generated)
			return 0;
		else
			return 1;
	} catch (...) {
		return 1;
	}
}

// �ر�SOCKET
// �Ƴ�������SOCKET��ص���Ϣ
void CSelectIO::onCloseSocket(const SOCKET s) {
	packet_handle_queue_.removeSOCKET(s);
}

// ��֤��ӦSOCKET�İ��Ƿ�Ӧ�ñ��洢
// �������ǻ�鿴��ʱ�����SOCKET�����Ƿ����, ���������ѧҪ����
// ��������ʹ��PEEK_MESSAGE����recv, �鿴��Ӧ��SOCKET�ǲ���HTTPЭ�飬
//  ������򱣴棬�������
bool CSelectIO::needStored(const SOCKET s) {
	// SOCKET s�Ƿ�����������İ������������ֱ�ӷ���true, ����������´���
	if (packet_handle_queue_.isThereUncompletePacket(s)) {
		return true;
	}

	// ��������ڰ���������
	if (checkWhiteDNS(s)) {
		return false;
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

		// ����Ƿ��ǰ�����
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

