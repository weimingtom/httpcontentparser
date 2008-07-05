#ifndef _UTILITY_HTTP_PACKET_H__
#define _UTILITY_HTTP_PACKET_H__

#include <utility\protocolpacket.h>
#include "syncutility.h"
#include <deque>

#define HTTP_PACKET_SIZE (1024)

class HTTPPacket;
class HTTP_RESPONSE_HEADER;
class HttpDataExtractor;

// HTTP头部的分割符\r\n
class HTTP_RESPONSE_HEADER {
public:
	HTTP_RESPONSE_HEADER();
	~HTTP_RESPONSE_HEADER();

	int parseHeader(const char *line, const int len);
	bool isHttpHeader(const char *line, const int len);
public:
	static const int    CONTYPE_HTML = 1;
	static const int    CONTYPE_CSS = 2;
	static const int    CONTYPE_JS = 3;
	static const int    CONTYPE_GIF = 100;
	static const int    CONTYPE_JPG = 101;
	static const int    CONTYPE_PNG = 102;


	static const int	TRANENCODING_CHUNKED = 1;
	static const int    CONTENCODING_GZIP = 1;
	static const int    NO_DESIGNATION = -1;
	static const int	CONNECT_CLOSE  = 1;
	static const int	CONNECT_KEEP_ALIVE = 2;

	int getContentLength() const { return content_length;}
	int getContentType() const { return content_type;}
	bool isChunk() const { return transfer_encoding == TRANENCODING_CHUNKED;}
	int getConnectionState() { return connection_state;}
	int getResponseCode() const { return response_code;}
private:
	int transfer_encoding;
	int content_type;
	int content_encoding;
	int content_length;
	int connection_state;
	int response_code;	// 返回代码，如404不可达
private:
	// 头部是否已经结束
	bool header_ended_; 
	// 分析行
	void parseLine(const char *line);
	static const int HTTP_HEADER_MAX_LENGTH = 64*1024;
	// 定义每条信息的最大长度
	static const int HTTP_HEADER_ITEMNAME_LENGTH = 256;
	static const int HTTP_HEADER_ITEMVALUE_LENGTH = 256;

	static const char * HEADER_FIRST ;
	static const char * HEADER_DATA ;
	static const char * HEADER_SERVER;
	static const char * HEADER_CONTENT_TYPE;
	static const char * HEADER_LAST_MODIFIY ;
	static const char * HEADER_CONTENT_LENGTH;
	static const char * HEADER_CONTENT_ENCODING;
	static const char * HEADER_CONNECTION;
	static const char * HEADER_TRANSFER_ENCODING;
	static const char * HEADER_ENDDING;

	// 头部
	static const char * HTTP_PROTOCOL_HEAD;
	static const char * HTTP_HEADER_TAIL;			// \r\n\r\n
	static const int  HTTP_HEADER_TAIL_LENGTH = 4;	// \r\n\r\n

	// 包内容
	static const char * CONTYPE_JPG_NAME;
	static const char * CONTYPE_CSS_NAME;
	static const char * CONTYPE_JS_NAME;
	static const char * CONTYPE_HTML_NAME;
	static const char * CONTYPE_GIF_NAME;
	static const char * CONTYPE_PNG_NAME;

	// 链接
	static const char * CONNECTION_KEEP_ALIVE_NAME;
	static const char * CONNECTION_CLOSE_NAME;

	// transfer_enconding
	static const char * TRANENCODING_CHUNKED_NAME;

	// content-encoding
	static const char * CONTENCODING_GZIP_NAME;

	// 禁用拷贝构造函数
	HTTP_RESPONSE_HEADER(HTTP_RESPONSE_HEADER&){}
};

// 用于保存一个完整的HTTP包
class HTTPPacket {
public:
	HTTPPacket(void);
	~HTTPPacket(void);

	// 当前包是一个完整的HTTP包吗？？
	bool isComplete() const;
	unsigned getDataSize() const;
	unsigned getHeaderSize() const;

	int addBuffer(const char *buf, const unsigned len);
	int read(char *buf, const int bufsize, int &bytedread);

	// 脱离下一个包， 当释放当前类时，不再释放与之相关联的包
	HTTPPacket * detachNext();

	int getContentType() { return http_header_.getContentType();}

	// 将..保存到文件当中
	int  achieve_data(const char * filename);
	int  achieve_header(const char * filename);
	int  achieve(const char * filename);

	// 此函数会返回一个原始的包，当然如果已经不存在了他会返回NULL
	ProtocolPacket<HTTP_PACKET_SIZE> * getRawPacket();

	// 获取头部
	const HTTP_RESPONSE_HEADER * getHeader() { return &http_header_;}

	// 用于唯一标识一个
	int  getCode() const { return code_; }
private:
	bool testHttpHeaderPacket(const char *buf, int len);
	// 本函数从给定数据中抽取一个数据单元，并将其加入到
	// 存储当中，而后返回存储单元的大小
	// 如果返回0，代表有错误发生
	int  extractData(const char *buf, const int len);

	// 如果当前包已经完成，使用下一个HTTPPacket进行相应。
	HTTPPacket *next_http_packet_;
	ProtocolPacket<HTTP_PACKET_SIZE> * http_data_;
	ProtocolPacket<HTTP_PACKET_SIZE> * http_header_achieve_;

	
	// 保存原始的包，按照接收到的顺序
	std::deque<ProtocolPacket<HTTP_PACKET_SIZE> * > raw_packets_;
	void addRawPacket(const char *buf, const int len);
	void clearRawDeque();

	// 分析协议头
	int parseHeader(const char *buffer, const unsigned len);

	// 获取下一个包
	HTTPPacket * getNextPacket();

	// 是否已经有头部
	bool header_exist_;

	// 包含重要数据
	HTTP_RESPONSE_HEADER http_header_;
	HttpDataExtractor * dataextractor_;

	int header_size_;
	int data_size_;

	bool header_read_;

	// 用于唯一标识一个HTTPPacket
	int code_;
	yanglei_utility::CAutoCreateCS cs_;
};

#endif  // _UTILITY_HTTP_PACKET_H__