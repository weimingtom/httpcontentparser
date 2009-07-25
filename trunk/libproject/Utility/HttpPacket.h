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

	INT_PTR parseHeader(const char *line, const INT_PTR len);
	bool isHttpHeader(const char *line, const INT_PTR len);
public:
	static const INT_PTR	TRANENCODING_CHUNKED = 1;
	static const INT_PTR    CONTENCODING_GZIP = 1;
	static const INT_PTR    NO_DESIGNATION = -1;
	static const INT_PTR	CONNECT_CLOSE  = 1;
	static const INT_PTR	CONNECT_KEEP_ALIVE = 2;

	INT_PTR getContentLength() const { return content_length;}
	INT_PTR getContentType() const { return content_type;}
	bool isChunk() const { return transfer_encoding == TRANENCODING_CHUNKED;}
	INT_PTR getConnectionState() const { return connection_state;}
	INT_PTR getResponseCode() const { return response_code;}
	INT_PTR getContentEncoding() const { return content_encoding;}

	// �Ƿ��������
	bool existContent() const ;

	const char * getDate()  const { return date;}
	const char * getServer() const { return server;}
	const char * getHeaderLine() const { return head_line;}
private:
	INT_PTR transfer_encoding;
	unsigned content_type;
	INT_PTR content_encoding;		// ���ݵı��뷽ʽ��gzip
	INT_PTR content_length;
	INT_PTR connection_state;
	INT_PTR response_code;	// ���ش��룬��404���ɴ�

	char server[128];
	char date[128];
	char head_line[128];
private:
	// ͷ���Ƿ��Ѿ�����
	bool header_ended_; 
	// ������
	void parseLine(const char *line);

public:
	static const INT_PTR HTTP_HEADER_MAX_LENGTH = 64*1024;
	// ����ÿ����Ϣ����󳤶�
	static const INT_PTR HTTP_HEADER_ITEMNAME_LENGTH = 256;
	static const INT_PTR HTTP_HEADER_ITEMVALUE_LENGTH = 256;

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
	static const INT_PTR  HTTP_HEADER_TAIL_LENGTH = 4;	// \r\n\r\n

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
	INT_PTR getDataSize() const;		// ��ȡ���ݴ�С
	INT_PTR getHeaderSize() const;		// ��ȡͷ����С

	INT_PTR addBuffer(const char *buf, const INT_PTR len, INT_PTR * written_length);
	INT_PTR read(char *buf, const INT_PTR bufsize, INT_PTR &bytedread);
	
	INT_PTR getContentType() const { return http_header_.getContentType();}

	// ��..���浽�ļ�����
	INT_PTR  achieve_data(const char * filename);
	// INT_PTR  achieve_header(const char * filename);
	INT_PTR  achieve(const char * filename);

	// �˺����᷵��һ��ԭʼ�İ�����Ȼ����Ѿ������������᷵��NULL
	ProtocolPacket<HTTP_PACKET_SIZE> * getRawPacket();

	// ��ȡͷ��
	const HTTP_RESPONSE_HEADER * getHeader() { return &http_header_;}

	// ����Ψһ��ʶһ��
	INT_PTR  getCode() const { return code_; }

	friend bool operator == (const HTTPPacket &p1, const HTTPPacket &p2) {
		return p1.getCode() == p2.getCode();
	}

	bool transfefTail();

	// �ͷ���Դ
	void releaseResource();
	ProtocolPacket<HTTP_PACKET_SIZE> * getData() { return http_data_; }
private:
	bool testHttpHeaderPacket(const char *buf, INT_PTR len);
	// �������Ӹ��������г�ȡһ�����ݵ�Ԫ����������뵽
	// �洢���У����󷵻ش洢��Ԫ�Ĵ�С
	// �������0�������д�����
	INT_PTR  extractData(const char *buf, const INT_PTR len);
	

	ProtocolPacket<HTTP_PACKET_SIZE> * http_data_;
	// ProtocolPacket<HTTP_PACKET_SIZE> * http_header_achieve_;

	
	// ����ԭʼ�İ������ս��յ���˳��
	ProtocolPacket<HTTP_PACKET_SIZE> *  raw_packets_;
	void addRawPacket(const char *buf, const INT_PTR len);
	void clearRawDeque();

	// ����Э��ͷ
	INT_PTR parseHeader(const char *buffer, const unsigned len);

	// �Ƿ����ͷ��
	bool existHeader() const;
	// �Ƿ��Ѿ���ͷ��
	bool header_exist_;  // �˱������ڴ���

	// ������Ҫ����
	HTTP_RESPONSE_HEADER http_header_;
	HttpDataExtractor * dataextractor_;

	INT_PTR header_size_;
	INT_PTR data_size_;

	bool header_read_;

	// ����Ψһ��ʶһ��HTTPPacket
	INT_PTR code_;
	static INT_PTR generateCode(); // ����һ������Ψһ��ʶ������ŵ�
	static INT_PTR cur_code_;
};

#endif  // _UTILITY_HTTP_PACKET_H__