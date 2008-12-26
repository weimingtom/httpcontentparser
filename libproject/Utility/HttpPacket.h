#ifndef _UTILITY_HTTP_PACKET_H__
#define _UTILITY_HTTP_PACKET_H__

#include <utility\protocolpacket.h>
#include "syncutility.h"
#include <deque>
#include <webcontenttype.h>

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
	static const int	TRANENCODING_CHUNKED = 1;
	static const int    CONTENCODING_GZIP = 1;
	static const int    NO_DESIGNATION = -1;
	static const int	CONNECT_CLOSE  = 1;
	static const int	CONNECT_KEEP_ALIVE = 2;

	int getContentLength() const { return content_length;}
	unsigned getContentType() const { return content_type;}
	bool isChunk() const { return transfer_encoding == TRANENCODING_CHUNKED;}
	int getConnectionState() const { return connection_state;}
	int getResponseCode() const { return response_code;}
	int getContentEncoding() const { return content_encoding;}

	// 是否存在内容
	bool existContent() const ;

	const char * getDate()  const { return date;}
	const char * getServer() const { return server;}
	const char * getHeaderLine() const { return head_line;}
private:
	int transfer_encoding;
	unsigned content_type;
	int content_encoding;		// 内容的编码方式如gzip
	int content_length;
	int connection_state;
	int response_code;	// 返回代码，如404不可达

	char server[128];
	char date[128];
	char head_line[128];
private:
	// 头部是否已经结束
	bool header_ended_; 
	// 分析行
	void parseLine(const char *line);

public:
	static const int HTTP_HEADER_MAX_LENGTH = 64*1024;
	// 定义每条信息的最大长度
	static const int HTTP_HEADER_ITEMNAME_LENGTH = 256;
	static const int HTTP_HEADER_ITEMVALUE_LENGTH = 256;

	static const char * HEADER_FIRST ;
	static const char * HEADER_DATE ;
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
	static const char * CONTYPE_XML_NAME;

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
	unsigned getDataSize() const;		// 获取数据大小
	unsigned getHeaderSize() const;		// 获取头部大小

	int addBuffer(const char *buf, const int len, int * written_length);
	int read(char *buf, const int bufsize, int &bytedread);
	
	unsigned getContentType() const { return http_header_.getContentType();}

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

	friend bool operator == (const HTTPPacket &p1, const HTTPPacket &p2) {
		return p1.getCode() == p2.getCode();
	}

	bool transfefTail();

	// 释放资源
	void releaseResource();
	ProtocolPacket<HTTP_PACKET_SIZE> * getData() { return http_data_; }
private:
	bool testHttpHeaderPacket(const char *buf, int len);
	// 本函数从给定数据中抽取一个数据单元，并将其加入到
	// 存储当中，而后返回存储单元的大小
	// 如果返回0，代表有错误发生
	int  extractData(const char *buf, const int len);
	

	ProtocolPacket<HTTP_PACKET_SIZE> * http_data_;
	ProtocolPacket<HTTP_PACKET_SIZE> * http_header_achieve_;

	
	// 保存原始的包，按照接收到的顺序
	ProtocolPacket<HTTP_PACKET_SIZE> *  raw_packets_;
	void addRawPacket(const char *buf, const int len);
	void clearRawDeque();

	// 分析协议头
	int parseHeader(const char *buffer, const unsigned len);

	// 是否存在头部
	bool existHeader() const;
	// 是否已经有头部
	bool header_exist_;  // 此变量存在错误

	// 包含重要数据
	HTTP_RESPONSE_HEADER http_header_;
	HttpDataExtractor * dataextractor_;

	int header_size_;
	int data_size_;

	bool header_read_;

	// 用于唯一标识一个HTTPPacket
	int code_;
	static int generateCode(); // 生成一个用于唯一标识这个符号的
	static int cur_code_;

	friend int FillBlankPacket(HTTPPacket *packet);
};

#endif  // _UTILITY_HTTP_PACKET_H__