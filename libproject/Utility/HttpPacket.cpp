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

	// 释放原始包
	clearRawDeque();
}

// 获取整个包的大小
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
// 将数据保存在文件当中
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
// 一下函数对原始数据包队列进行操作
void HTTPPacket::clearRawDeque() {
	delete raw_packets_;
}

void HTTPPacket::addRawPacket(const char *buf, const int len) {
	// 如果此函数分配内存失败，外层程序会处理相应异常
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
// 验证HTTP包，并将其加入到保重
// 如果返回0, 则表示不是HTTP包
int HTTPPacket::addBuffer(const char *buf, const unsigned len) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);

		int bytes = 0;
		// 循环调用指导数据处理完成
		// 因为chunk编码方式可能多个包存在于一个物理包当中。。
		// 所以必须不断的提取，知道数据结束
		while (bytes != len) {
			int bytes_read = extractData(&(buf[bytes]), len - bytes);
			
			// 如果读取为0， 代表获取了一个包
			if (bytes_read == 0)
				break;

			// 将处理过的原始数据加入进去
			addRawPacket(&(buf[bytes]), bytes_read);
			bytes += bytes_read;
		}
		return bytes;
	} catch(int) {
		WriteLog("E:\\workspace\\debuglog\\addbufferexp.log", 0, buf, len);
		DEBUG_MESSAGE("addBuffer int exception...");
		return 0;
	} catch (std::bad_alloc &) {
		// 如果内存不足，交给上层程序来处理
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
	// 如果包尚未完成，且不存在头部
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


		// 如果还没有初始化，且传入的数据是HTTP协议
		header_size_ = parseHeader(buf, len);	// 分析头部，并返回大小
		if (header_size_ == 0) // 可能不是一个HTTP协议
			throw 0;


		http_data_ = new ProtocolPacket<HTTP_PACKET_SIZE>(); // 存储空间
		http_header_achieve_ = new ProtocolPacket<HTTP_PACKET_SIZE>();// 存储头部
				
		// 保存头部
		http_header_achieve_->write(buf, header_size_);
		dataextractor_ = HttpDataExtractor::Create(&http_header_, http_data_);

		int bytes_dealed = header_size_ +
			dataextractor_->addBuffer(&(buf[header_size_]), len - header_size_);

		if (bytes_dealed != 0) {
			header_exist_ = true;
		}

		return bytes_dealed;
	} else if (!isComplete() && header_exist_ == true) {
		// 如果已经得到了头部，且传入的数据不是
		// 那么得到的数据就是
		assert ( addBuffer != NULL);
		return  dataextractor_->addBuffer(buf, len);
	} else if (isComplete() && header_exist_ == false) {
		assert(false);
		throw (0);
		return 0;
	}

	return 0; // 其实不会到这里的...
}
bool HTTPPacket::testHttpHeaderPacket(const char *buf, int len) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	return http_header_.isHttpHeader(buf, len);
}

// 分析HTTP协议头
// 保存HTTP协议的内容，而后获取头
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

// 头部
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


// HTTP头部的结束符
const char * HTTP_RESPONSE_HEADER::HTTP_HEADER_TAIL  = "\r\n\r\n";

// transfer_enconding
const char * HTTP_RESPONSE_HEADER::TRANENCODING_CHUNKED_NAME = "chunked";
// const int HTTP_RESPONSE_HEADER::TRANENCODING_CHUNKED = 1;

// content-encoding
const char * HTTP_RESPONSE_HEADER::CONTENCODING_GZIP_NAME = "gzip";
// const int    HTTP_RESPONSE_HEADER::CONTENCODING_GZIP = 1;

// 链接
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

	// 测试开头结尾是否是一个有效的包
	if (strstr(header_data, "HTTP") != header_data) {
		return 0;
	}

	// 未找到HTTP头不得结尾，应该是个错误包！！
	const char * http_header_tail = strstr(header_data, HTTP_HEADER_TAIL);
	if (http_header_tail == NULL) {
		return 0;
	}

	// 复制数据
	buf[len] = '\0';
	memcpy(buf, header_data, len);
 
	char seps[] = "\n";
	char * token = strtok(buf, seps);
	while( token != NULL && header_ended_ == false)  {
		// 分析行
		parseLine(token);
		token = strtok( NULL, seps );
	}

	// 在解析完成以后仍然有一些重要的值处于未指定状态
	// 那么应该不是一个HTTP协议
	//if ( NO_DESIGNATION == content_type) {
	//	return 0;
	//}

	// 返回整个头部的大小
	const int total_header_length = HTTP_HEADER_TAIL_LENGTH + http_header_tail - header_data;
	assert(len >= total_header_length);
	return total_header_length;
}

void HTTP_RESPONSE_HEADER::parseLine(const char *linedata) {
	if (linedata == strstr(linedata, HEADER_FIRST)) {
		// http都不 ： HTTP/1.1 203 XX
		char * code_ptr = strstr(linedata, " "); // 寻找空格
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
		// 长度
		const char * str_content_length = strchr(linedata, ':');
		// 从':'之后开始
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