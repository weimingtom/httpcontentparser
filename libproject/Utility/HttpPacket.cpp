#include "StdAfx.h"
#include ".\HTTPPacket.h"
#include <utility\protocolpacket.h>
#include <string>
#include ".\strutility.h"
#include <ostream>
#include <fstream>
#include <ios>
#include <logdebug.h>
#include "httpdataextractor.h"

//=================================================
// class HTTPPacket
HTTPPacket::HTTPPacket(void) {
	http_data_ = NULL;
	header_exist_ = false;
	dataextractor_ = NULL;

	header_size_ = 0;
	data_size_ = 0;
	http_header_achieve_ = NULL;

	header_read_  = false;

	raw_packets_ = NULL;

	code_ = GetTickCount();
}

HTTPPacket::~HTTPPacket(void) {
	if (NULL != dataextractor_) {
		delete dataextractor_;
		dataextractor_ = NULL;
	}

	if (NULL != http_data_) {
		delete http_data_;
		http_data_ = NULL;
	}

	// �ͷ�ԭʼ��
	clearRawDeque();
}

// ��ȡ�������Ĵ�С
bool HTTPPacket::isComplete()  const {
	if (dataextractor_ == NULL)
		return false;
	else 
		return dataextractor_->finished();
}

unsigned HTTPPacket::getHeaderSize() const {
	return header_size_;
}

unsigned HTTPPacket::getDataSize() const { 
	if (http_data_ != NULL)
		return http_data_->getTotalSize();
	else
		return 0;
}

/////////////////////////////////////////////////////
// �����ݱ������ļ�����
int HTTPPacket::achieve(const char * filename) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	int header_length = achieve_header(filename);
	int data_length = achieve_data(filename);
	return header_length + data_length;
}
int  HTTPPacket::achieve_data(const char * filename) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	if (NULL != http_data_)
		return http_data_->achieve(filename);
	else
		return 0;
}

int  HTTPPacket::achieve_header(const char * filename) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	if (NULL != http_header_achieve_)
		return http_header_achieve_->achieve(filename);
	else
		return 0;
}

///////////////////////////////////////////////
// һ�º�����ԭʼ���ݰ����н��в���
void HTTPPacket::clearRawDeque() {
	delete raw_packets_;
}

void HTTPPacket::addRawPacket(const char *buf, const int len) {
	// ����˺��������ڴ�ʧ�ܣ�������ᴦ����Ӧ�쳣
	if (raw_packets_ == NULL)
		raw_packets_ = new ProtocolPacket<HTTP_PACKET_SIZE>();
	raw_packets_->write(buf, len);
}

ProtocolPacket<HTTP_PACKET_SIZE> * HTTPPacket::getRawPacket() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_); 
	return raw_packets_;
}

////////////////////////////////////////////
// ��֤HTTP������������뵽����
// �������0, ���ʾ����HTTP��
int HTTPPacket::addBuffer(const char *buf, const unsigned len) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);

		int bytes = 0;
		// ѭ������ָ�����ݴ������
		// ��Ϊchunk���뷽ʽ���ܶ����������һ����������С���
		// ���Ա��벻�ϵ���ȡ��֪�����ݽ���
		while (bytes != len) {
			int bytes_read = extractData(&(buf[bytes]), len - bytes);
			
			// �����ȡΪ0�� �����ȡ��һ����
			if (bytes_read == 0)
				break;

			// ���������ԭʼ���ݼ����ȥ
			addRawPacket(&(buf[bytes]), bytes_read);
			bytes += bytes_read;
		}
		return bytes;
	} catch(int) {
		WriteLog("E:\\workspace\\debuglog\\addbufferexp.log", 0, buf, len);
		DEBUG_MESSAGE("addBuffer int exception...");
		return 0;
	} catch (std::bad_alloc &) {
		// ����ڴ治�㣬�����ϲ����������
		throw; 
	} catch (...) {
		char filename[1024];
		sprintf(filename, "E:\\workspace\\debuglog\\int%d.log", getCode());
		achieve(filename);

		WriteLog("E:\\workspace\\debuglog\\addbufferexp.log", 0, buf, len);
		DEBUG_MESSAGE("addBuffer exception...");
		return 0;
	}
}

int HTTPPacket::read(char *buf, const int bufsize, int &bytedread) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	int head_bytes_read = 0;
	int data_bytes_read = 0;
	if (header_read_ == false) {
		header_read_ = true;
		head_bytes_read = http_header_achieve_->read(buf, bufsize);
	}

	data_bytes_read = http_data_->read(buf, bufsize - head_bytes_read);
	bytedread = head_bytes_read + data_bytes_read;
	return http_data_->getBytesCanRead();
}

int HTTPPacket::extractData(const char *buf, const int len) {
	// �������δ��ɣ��Ҳ�����ͷ��
	if (!isComplete() && header_exist_ == false) {
		if (!testHttpHeaderPacket(buf, len)) {
			OutputDebugString("throw exception...");
			throw int(0);
			return 0; 
		}

		assert (dataextractor_ == NULL);
		assert ( len >= header_size_);
		assert ( http_data_ == NULL);
		assert ( http_header_achieve_ == NULL);


		// �����û�г�ʼ�����Ҵ����������HTTPЭ��
		header_size_ = parseHeader(buf, len);	// ����ͷ���������ش�С
		if (header_size_ == 0) // ���ܲ���һ��HTTPЭ��
			throw 0;


		http_data_ = new ProtocolPacket<HTTP_PACKET_SIZE>(); // �洢�ռ�
		http_header_achieve_ = new ProtocolPacket<HTTP_PACKET_SIZE>();// �洢ͷ��
				
		// ����ͷ��
		http_header_achieve_->write(buf, header_size_);
		dataextractor_ = HttpDataExtractor::Create(&http_header_, http_data_);

		int bytes_dealed = header_size_ +
			dataextractor_->addBuffer(&(buf[header_size_]), len - header_size_);

		if (bytes_dealed != 0) {
			header_exist_ = true;
		}

		return bytes_dealed;
	} else if (!isComplete() && header_exist_ == true) {
		// ����Ѿ��õ���ͷ�����Ҵ�������ݲ���
		// ��ô�õ������ݾ���
		assert ( addBuffer != NULL);
		return  dataextractor_->addBuffer(buf, len);
	} else if (isComplete() && header_exist_ == false) {
		assert(false);
		throw (0);
		return 0;
	}

	return 0; // ��ʵ���ᵽ�����...
}
bool HTTPPacket::testHttpHeaderPacket(const char *buf, int len) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	return http_header_.isHttpHeader(buf, len);
}

// ����HTTPЭ��ͷ
// ����HTTPЭ������ݣ������ȡͷ
int HTTPPacket::parseHeader(const char *buffer_recv, const unsigned len) {
	header_size_ =  http_header_.parseHeader(buffer_recv, len);
	return header_size_;
}
//=================================================
//


//=================================================
// class HTTP_HEADER
const char * HTTP_RESPONSE_HEADER::HEADER_FIRST = "HTTP/";
const char * HTTP_RESPONSE_HEADER::HEADER_DATA = "Date:";
const char * HTTP_RESPONSE_HEADER::HEADER_SERVER = "Server:";
const char * HTTP_RESPONSE_HEADER::HEADER_CONTENT_TYPE = "Content-Type:";
const char * HTTP_RESPONSE_HEADER::HEADER_LAST_MODIFIY = "Last-modified:";
const char * HTTP_RESPONSE_HEADER::HEADER_CONTENT_LENGTH = "Content-Length:";
const char * HTTP_RESPONSE_HEADER::HEADER_CONTENT_ENCODING = "Content-Encoding:";
const char * HTTP_RESPONSE_HEADER::HEADER_CONNECTION = "Connection:";
const char * HTTP_RESPONSE_HEADER::HEADER_TRANSFER_ENCODING = "Transfer-Encoding:";
const char * HTTP_RESPONSE_HEADER::HEADER_ENDDING = "\r\n\r\n";

// ͷ��
const char * HTTP_RESPONSE_HEADER::HTTP_PROTOCOL_HEAD = "HTTP";

// content_type
// const int    HTTP_RESPONSE_HEADER::CONTYPE_GIF = 100;
const char * HTTP_RESPONSE_HEADER::CONTYPE_GIF_NAME	= "image/gif";
// const int    HTTP_RESPONSE_HEADER::CONTYPE_JPG = 101;
const char * HTTP_RESPONSE_HEADER::CONTYPE_JPG_NAME	= "image/jpeg";
// static const int    HTTP_RESPONSE_HEADER::CONTYPE_PNG = 102;
static const char * CONTYPE_PNG_NAME = "image/png";

// const int    HTTP_RESPONSE_HEADER::CONTYPE_HTML =1;
const char * HTTP_RESPONSE_HEADER::CONTYPE_HTML_NAME	="text/html";
// const int    HTTP_RESPONSE_HEADER::CONTYPE_CSS= 2;
const char * HTTP_RESPONSE_HEADER::CONTYPE_CSS_NAME	= "text/css";
// const int    HTTP_RESPONSE_HEADER::CONTYPE_JS = 3;
const char * HTTP_RESPONSE_HEADER::CONTYPE_JS_NAME	= "application/x-javascript";


// HTTPͷ���Ľ�����
const char * HTTP_RESPONSE_HEADER::HTTP_HEADER_TAIL  = "\r\n\r\n";

// transfer_enconding
const char * HTTP_RESPONSE_HEADER::TRANENCODING_CHUNKED_NAME = "chunked";
// const int HTTP_RESPONSE_HEADER::TRANENCODING_CHUNKED = 1;

// content-encoding
const char * HTTP_RESPONSE_HEADER::CONTENCODING_GZIP_NAME = "gzip";
// const int    HTTP_RESPONSE_HEADER::CONTENCODING_GZIP = 1;

// ����
const char * HTTP_RESPONSE_HEADER::CONNECTION_KEEP_ALIVE_NAME = "keep-alive";
const char * HTTP_RESPONSE_HEADER::CONNECTION_CLOSE_NAME = "close";

HTTP_RESPONSE_HEADER::HTTP_RESPONSE_HEADER() {
	transfer_encoding	= NO_DESIGNATION;
	content_type		= NO_DESIGNATION;
	content_encoding	= NO_DESIGNATION;
	content_length		= NO_DESIGNATION;
	connection_state    = NO_DESIGNATION;
	response_code		= NO_DESIGNATION;

	header_ended_ = false;
}

HTTP_RESPONSE_HEADER::~HTTP_RESPONSE_HEADER() {
} 

int HTTP_RESPONSE_HEADER::parseHeader(const char *header_data, const int len) {
	char buf[HTTP_HEADER_MAX_LENGTH];
	assert(HTTP_HEADER_MAX_LENGTH > len);

	// ���Կ�ͷ��β�Ƿ���һ����Ч�İ�
	if (strstr(header_data, "HTTP") != header_data) {
		return 0;
	}

	// δ�ҵ�HTTPͷ���ý�β��Ӧ���Ǹ����������
	const char * http_header_tail = strstr(header_data, HTTP_HEADER_TAIL);
	if (http_header_tail == NULL) {
		return 0;
	}

	// ��������
	buf[len] = '\0';
	memcpy(buf, header_data, len);
 
	char seps[] = "\n";
	char * token = strtok(buf, seps);
	while( token != NULL && header_ended_ == false)  {
		// ������
		parseLine(token);
		token = strtok( NULL, seps );
	}

	// �ڽ�������Ժ���Ȼ��һЩ��Ҫ��ֵ����δָ��״̬
	// ��ôӦ�ò���һ��HTTPЭ��
	//if ( NO_DESIGNATION == content_type) {
	//	return 0;
	//}

	// ��������ͷ���Ĵ�С
	const int total_header_length = HTTP_HEADER_TAIL_LENGTH + http_header_tail - header_data;
	assert(len >= total_header_length);
	return total_header_length;
}

void HTTP_RESPONSE_HEADER::parseLine(const char *linedata) {
	if (linedata == strstr(linedata, HEADER_FIRST)) {
		// http���� �� HTTP/1.1 203 XX
		char * code_ptr = strstr(linedata, " "); // Ѱ�ҿո�
		if (NULL != code_ptr) {
			response_code = atoi(code_ptr);
		}
	} else if (linedata == strstr(linedata, HEADER_CONTENT_TYPE)) {
		if (strstr(linedata, CONTYPE_GIF_NAME)) {
			content_type = CONTYPE_GIF;
		} else if (strstr(linedata, CONTYPE_JPG_NAME)) {
			content_type = CONTYPE_JPG;
		}  else if (strstr(linedata, CONTYPE_CSS_NAME)) {
			content_type = CONTYPE_CSS;
		}  else if (strstr(linedata, CONTYPE_JS_NAME)) {
			content_type = CONTYPE_JS;
		}  else if (strstr(linedata, CONTYPE_HTML_NAME)) {
			content_type = CONTYPE_HTML;
		}  else {
			content_type = CONTYPE_UNKNOWN;
		}
	} else if (linedata == strstr(linedata, HEADER_TRANSFER_ENCODING)) {
		if (strstr(linedata, TRANENCODING_CHUNKED_NAME)) {
			transfer_encoding = TRANENCODING_CHUNKED;
		} else {
			transfer_encoding = NO_DESIGNATION;
		}
	} else if (linedata == strstr(linedata, HEADER_CONTENT_ENCODING)) {
		if (strstr(linedata, CONTENCODING_GZIP_NAME)) {
			content_encoding = CONTENCODING_GZIP;
		} else {
			content_encoding = NO_DESIGNATION;
		}
	} else if (linedata == strstr(linedata, HEADER_CONTENT_LENGTH)) {
		// ����
		const char * str_content_length = strchr(linedata, ':');
		// ��':'֮��ʼ
		content_length = atoi(&(str_content_length[1]));
	} else if (linedata == strstr(linedata, HEADER_CONNECTION)) {
		if (strstr(linedata, CONNECTION_CLOSE_NAME)) {
			connection_state = CONNECT_CLOSE;
		} else if (strstr(linedata, CONNECTION_KEEP_ALIVE_NAME)) {
			connection_state = CONNECT_KEEP_ALIVE;
		} else {
			connection_state = NO_DESIGNATION;
		}
	} else if (linedata == strstr(linedata, "\r")) {
		header_ended_ = true;
	}
}

bool HTTP_RESPONSE_HEADER::isHttpHeader(const char *line, const int len) {
	if (len < 4) return false;
	if(line == strstr(line, HTTP_PROTOCOL_HEAD) /*&& NULL != strstr(line, "\r\n")*/)
		return true;
	else 
		return false;
}