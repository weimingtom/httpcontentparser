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

// HTTPͷ���ķָ��\r\n
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

	// �Ƿ��������
	bool existContent() const ;

	const char * getDate()  const { return date;}
	const char * getServer() const { return server;}
	const char * getHeaderLine() const { return head_line;}
private:
	int transfer_encoding;
	unsigned content_type;
	int content_encoding;		// ���ݵı��뷽ʽ��gzip
	int content_length;
	int connection_state;
	int response_code;	// ���ش��룬��404���ɴ�

	char server[128];
	char date[128];
	char head_line[128];
private:
	// ͷ���Ƿ��Ѿ�����
	bool header_ended_; 
	// ������
	void parseLine(const char *line);

public:
	static const int HTTP_HEADER_MAX_LENGTH = 64*1024;
	// ����ÿ����Ϣ����󳤶�
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

	// ͷ��
	static const char * HTTP_PROTOCOL_HEAD;
	static const char * HTTP_HEADER_TAIL;			// \r\n\r\n
	static const int  HTTP_HEADER_TAIL_LENGTH = 4;	// \r\n\r\n

	// ������
	static const char * CONTYPE_JPG_NAME;
	static const char * CONTYPE_CSS_NAME;
	static const char * CONTYPE_JS_NAME;
	static const char * CONTYPE_HTML_NAME;
	static const char * CONTYPE_GIF_NAME;
	static const char * CONTYPE_PNG_NAME;
	static const char * CONTYPE_XML_NAME;

	// ����
	static const char * CONNECTION_KEEP_ALIVE_NAME;
	static const char * CONNECTION_CLOSE_NAME;

	// transfer_enconding
	static const char * TRANENCODING_CHUNKED_NAME;

	// content-encoding
	static const char * CONTENCODING_GZIP_NAME;

	// ���ÿ������캯��
	HTTP_RESPONSE_HEADER(HTTP_RESPONSE_HEADER&){}
};

// ���ڱ���һ��������HTTP��
class HTTPPacket {
public:
	HTTPPacket(void);
	~HTTPPacket(void);

	// ��ǰ����һ��������HTTP���𣿣�
	bool isComplete() const;
	unsigned getDataSize() const;		// ��ȡ���ݴ�С
	unsigned getHeaderSize() const;		// ��ȡͷ����С

	int addBuffer(const char *buf, const int len, int * written_length);
	int read(char *buf, const int bufsize, int &bytedread);
	
	unsigned getContentType() const { return http_header_.getContentType();}

	// ��..���浽�ļ�����
	int  achieve_data(const char * filename);
	int  achieve_header(const char * filename);
	int  achieve(const char * filename);

	// �˺����᷵��һ��ԭʼ�İ�����Ȼ����Ѿ������������᷵��NULL
	ProtocolPacket<HTTP_PACKET_SIZE> * getRawPacket();

	// ��ȡͷ��
	const HTTP_RESPONSE_HEADER * getHeader() { return &http_header_;}

	// ����Ψһ��ʶһ��
	int  getCode() const { return code_; }

	friend bool operator == (const HTTPPacket &p1, const HTTPPacket &p2) {
		return p1.getCode() == p2.getCode();
	}

	bool transfefTail();

	// �ͷ���Դ
	void releaseResource();
	ProtocolPacket<HTTP_PACKET_SIZE> * getData() { return http_data_; }
private:
	bool testHttpHeaderPacket(const char *buf, int len);
	// �������Ӹ��������г�ȡһ�����ݵ�Ԫ����������뵽
	// �洢���У����󷵻ش洢��Ԫ�Ĵ�С
	// �������0�������д�����
	int  extractData(const char *buf, const int len);
	

	ProtocolPacket<HTTP_PACKET_SIZE> * http_data_;
	ProtocolPacket<HTTP_PACKET_SIZE> * http_header_achieve_;

	
	// ����ԭʼ�İ������ս��յ���˳��
	ProtocolPacket<HTTP_PACKET_SIZE> *  raw_packets_;
	void addRawPacket(const char *buf, const int len);
	void clearRawDeque();

	// ����Э��ͷ
	int parseHeader(const char *buffer, const unsigned len);

	// �Ƿ����ͷ��
	bool existHeader() const;
	// �Ƿ��Ѿ���ͷ��
	bool header_exist_;  // �˱������ڴ���

	// ������Ҫ����
	HTTP_RESPONSE_HEADER http_header_;
	HttpDataExtractor * dataextractor_;

	int header_size_;
	int data_size_;

	bool header_read_;

	// ����Ψһ��ʶһ��HTTPPacket
	int code_;
	static int generateCode(); // ����һ������Ψһ��ʶ������ŵ�
	static int cur_code_;

	friend int FillBlankPacket(HTTPPacket *packet);
};

#endif  // _UTILITY_HTTP_PACKET_H__