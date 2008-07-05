#include "StdAfx.h"
#include ".\httppackettest.h"
#include <utility\HttpPacket.h>
#include <utility\protocolpacket.h>

const char packet1[] = 	"HTTP/1.1 302 Found\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
"Vary: Accept-Encoding\r\n"
"Cache-Control: max-age=5184000\r\n"
"Expires: Mon, 23 Jun 2008 02:37:48 GMT\r\n"
"Last-Modified: Fri, 08 Jun 2007 03:13:16 GMT\r\n"
"ETag: \"434610-296-4668c94c\"\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 682\r\n"
"Content-Type: text/html\r\n"
"Age: 220737\r\n"
"X-Cache: HIT from 168479083.sohu.com\r\n"
"Connection: close\r\n\r\n"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012";	// 682

const char packet2[] = 	"HTTP/1.1 302 Found\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Cache-Control: max-age=5184000\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 234\r\n"
"Content-Type: image/gif\r\n"
"Age: 220737\r\n"
"X-Cache: HIT from 168479083.sohu.com\r\n"
"Connection: keep-alive\r\n\r\n"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"1234567890123456789012345678901234"; // 234

const char packet3[] = 	"HTTP/1.1 302 Found\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Last-Modified: Fri, 08 Jun 2007 03:13:16 GMT\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 62\r\n"
"Content-Type: image/jpeg\r\n"
"Age: 220737\r\n"
"X-Cache: HIT from 168479083.sohu.com\r\n"
"Connection: close\r\n\r\n"
"12345678901234567890123456789012345678901234567890"
"123456789012";

const char packet4[] = "HTTP/1.1 200 OK\r\n"
"Cache-Control: private, max-age=0\r\n"
"Date: Fri, 13 Jun 2008 13:59:34 GMT\r\n"
"Expires: -1\r\n"
"Content-Type: text/html; charset=UTF-8\r\n"
"Content-Encoding: gzip\r\n"
"Server: gws\r\n"
"Transfer-Encoding: chunked\r\n\r\n"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890"
"12345678901234567890123456789012345678901234567890";

const char packet5[] = "xtyHTTP/1.1 200 OK\r\n"
"Cache-Control: private, max-age=0\r\n";


const char packet6[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
		"Vary: Accept-Encoding\r\n"
		"Content-Length: 3\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n\r\n"
		"HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
		"Vary: Accept-Encoding\r\n"
		"Content-Length: 8283\r\n"
		"Content-Type: image/gif\r\n"
		"Connection: close\r\n\r\n"
		"HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
		"Vary: Accept-Encoding\r\n"
		"Content-Length: 231\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n\r\n"
		"HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
		"Vary: Accept-Encoding\r\n"
		"Content-Length: 09\r\n"
		"Content-Type: image/jpeg\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: close\r\n\r\n";

const char series1[] = "HTTP/1.1 200 OK\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
"Vary: Accept-Encoding\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 234\r\n"
"Content-Type: image/gif\r\n"
"Age: 220737\r\n"
"X-Cache: HIT from 168479083.sohu.com\r\n"
"Connection: keep-alive\r\n\r\n";

const char series2[] = "12345678901234567890123456789012345678901234567890";
const char series3[] = "12345678901234567890123456789012345678901234567890";
const char series4[] = "12345678901234567890123456789012345678901234567890";
const char series5[] = "12345678901234567890123456789012345678901234567890";
const char series6[] = "1234567890123456789012345678901234";

const char chunk1[] = "HTTP/1.1 200 OK\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"ETag: \"434610-296-4668c94c\"\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Type: image/gif\r\n"
"Age: 220737\r\n"
"Transfer-Encoding: chunked\r\n"
"Connection: keep-alive\r\n\r\n";

const char chunk2[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n";
const char chunk3[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n";
const char chunk4[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n";
const char chunk5[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n";
const char chunk6[] = "0\r\n\r\n";



HTTPPacketTest::HTTPPacketTest(void) {
}
 
HTTPPacketTest::~HTTPPacketTest(void) {
}

void HTTPPacketTest::testNoContentPacket() {
	const char no_content[] = "HTTP/1.0 304 Not Modified\r\n"
							"Date: Mon, 30 Jun 2008 16:09:18 GMT\r\n"
							"Content-Type: application/x-shockwave-flash\r\n"
							"Expires: Mon, 30 Jun 2008 16:14:18 GMT\r\n"
							"Last-Modified: Fri, 06 Jun 2008 04:23:13 GMT\r\n"
							"Age: 297\r\n"
							"X-Cache: HIT from 153-147.sina.com.cn\r\n"
							"Connection: keep-alive\r\n\r\n";

	HTTP_RESPONSE_HEADER header1;
	header1.parseHeader(no_content, strlen(no_content));
	CPPUNIT_ASSERT(header1.isChunk()== false);
	CPPUNIT_ASSERT(header1.getResponseCode() == 304);

	HTTPPacket *packet = new HTTPPacket;
	packet->addBuffer(no_content, strlen(no_content));
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;
}

void HTTPPacketTest::testSeriesPacket() {
	const char packet1[] = 	"HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
	"Vary: Accept-Encoding\r\n"
	"Cache-Control: max-age=5184000\r\n"
	"Expires: Mon, 23 Jun 2008 02:37:48 GMT\r\n"
	"Last-Modified: Fri, 08 Jun 2007 03:13:16 GMT\r\n"
	"ETag: \"434610-296-4668c94c\"\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 2\r\n"
	"Content-Type: text/html\r\n"
	"Age: 220737\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: close\r\n\r\n"
	"aa"
	"HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
	"Vary: Accept-Encoding\r\n"
	"Cache-Control: max-age=5184000\r\n"
	"Expires: Mon, 23 Jun 2008 02:37:48 GMT\r\n"
	"Last-Modified: Fri, 08 Jun 2007 03:13:16 GMT\r\n"
	"ETag: \"434610-296-4668c94c\"\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 3\r\n"
	"Content-Type: text/html\r\n"
	"Age: 220737\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: close\r\n\r\n"
	"aaa"
	"HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Server: Apache/1.3.37 (Unix) mod_gzip/1.3.26.1\r\n"
	"Vary: Accept-Encoding\r\n"
	"Cache-Control: max-age=5184000\r\n"
	"Expires: Mon, 23 Jun 2008 02:37:48 GMT\r\n"
	"Last-Modified: Fri, 08 Jun 2007 03:13:16 GMT\r\n"
	"ETag: \"434610-296-4668c94c\"\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 6\r\n"
	"Content-Type: text/html\r\n"
	"Age: 220737\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: close\r\n\r\n"
	"aaaaaa";

	HTTPPacket *packet = new HTTPPacket;
	packet->addBuffer(packet1, strlen(packet1));

	HTTPPacket *p1 = packet->detachNext();
	CPPUNIT_ASSERT(true == packet->isComplete());
	CPPUNIT_ASSERT(packet->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	delete packet;

	HTTPPacket *p2 = p1->detachNext();
	CPPUNIT_ASSERT(true == p1->isComplete());
	CPPUNIT_ASSERT(p1->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	delete p1;

	HTTPPacket *p3 = p2->detachNext();
	CPPUNIT_ASSERT(true == p2->isComplete());
	CPPUNIT_ASSERT(p2->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	delete p2;
}

void HTTPPacketTest::testWrongHeader() {
	HTTPPacket *packet = new HTTPPacket;
	char buffer1[] = "HTTP"; 
	char buffer2[] = "HTTP aidji8vz2\r\noaijdfoin\r\n\r\n";
	CPPUNIT_ASSERT(0 == packet->addBuffer(buffer1, strlen(buffer1)));
//	CPPUNIT_ASSERT(0 == packet->addBuffer(buffer2, strlen(buffer2)));
}

// 测试获取原始数据包
void HTTPPacketTest::testRawPacket() {
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(chunk1) == packet->addBuffer(chunk1, strlen(chunk1)));
	CPPUNIT_ASSERT(strlen(chunk2) == packet->addBuffer(chunk2, strlen(chunk2)));
	CPPUNIT_ASSERT(strlen(chunk3) == packet->addBuffer(chunk3, strlen(chunk3)));
	CPPUNIT_ASSERT(strlen(chunk4) == packet->addBuffer(chunk4, strlen(chunk4)));
	CPPUNIT_ASSERT(strlen(chunk5) == packet->addBuffer(chunk5, strlen(chunk5)));
	CPPUNIT_ASSERT(strlen(chunk6) == packet->addBuffer(chunk6, strlen(chunk6)));

	const int buf_len = 1024 * 64;
	char buffer[buf_len];

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet1 = packet->getRawPacket();
	int len1 = raw_packet1->read(buffer, buf_len);
	buffer[len1+1] = '\0';
	CPPUNIT_ASSERT(len1 == strlen(chunk1));
	CPPUNIT_ASSERT(strcmp(chunk1, buffer));

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet2 = packet->getRawPacket();
	int len2 = raw_packet2->read(buffer, buf_len);
	buffer[len2+1] = '\0';
	CPPUNIT_ASSERT(len2 == strlen(chunk2));
	CPPUNIT_ASSERT(strcmp(chunk2, buffer));

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet3 = packet->getRawPacket();
	int len3 = raw_packet3->read(buffer, buf_len);
	buffer[len3+1] = '\0';
	CPPUNIT_ASSERT(len3 == strlen(chunk3));
	CPPUNIT_ASSERT(strcmp(chunk3, buffer));

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet4 = packet->getRawPacket();
	int len4 = raw_packet4->read(buffer, buf_len);
	buffer[len4+1] = '\0';
	CPPUNIT_ASSERT(len4 == strlen(chunk4));
	CPPUNIT_ASSERT(strcmp(chunk1, buffer));

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet5 = packet->getRawPacket();
	int len5 = raw_packet5->read(buffer, buf_len);
	buffer[len5+1] = '\0';
	CPPUNIT_ASSERT(len5 == strlen(chunk5));
	CPPUNIT_ASSERT(strcmp(chunk5, buffer));

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet6 = packet->getRawPacket();
	int len6 = raw_packet6->read(buffer, buf_len);
	buffer[len6+1] = '\0';
	CPPUNIT_ASSERT(len6 == strlen(chunk6));
	CPPUNIT_ASSERT(strcmp(chunk6, buffer));
	
	delete packet;
}

// 测试编码方式为chunk的HTTP包
void HTTPPacketTest::testChunk() {
	{ 
	// 添加一个连续的
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(chunk1) == packet->addBuffer(chunk1, strlen(chunk1)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(chunk2) == packet->addBuffer(chunk2, strlen(chunk2)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(chunk3) == packet->addBuffer(chunk3, strlen(chunk3)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 2);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(chunk4) == packet->addBuffer(chunk4, strlen(chunk4)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 3);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(chunk5) == packet->addBuffer(chunk5, strlen(chunk5)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 4);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(chunk6) == packet->addBuffer(chunk6, strlen(chunk6)));
	CPPUNIT_ASSERT(packet->getDataSize() == 200);
	CPPUNIT_ASSERT(packet->isComplete() == true);
	HTTPPacket *p = packet->detachNext();
	CPPUNIT_ASSERT(p == NULL);
	delete packet;
	}

	{
	// test complex chunk
	const char complex_chunk1[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: keep-alive\r\n\r\n";

	const char complex_chunk2[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n";
	const char complex_chunk3[] = "32\r\n12345678901234567890123456789012345678901234567890\r\n"
		"12C\r\n12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890"
		"12345678901234567890123456789012345678901234567890";
	const char complex_chunk4[] = "12345678901234567890123456789012345678901234567890";
	const char complex_chunk5[] = "12345678901234567890123456789012345678901234567890\r\n0\r\n\r\n";
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(complex_chunk1) == packet->addBuffer(complex_chunk1, strlen(complex_chunk1)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(complex_chunk2) == packet->addBuffer(complex_chunk2, strlen(complex_chunk2)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(complex_chunk3) == packet->addBuffer(complex_chunk3, strlen(complex_chunk3)));
	CPPUNIT_ASSERT(packet->getDataSize() == 300);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(strlen(complex_chunk4) == packet->addBuffer(complex_chunk4, strlen(complex_chunk4)));
	CPPUNIT_ASSERT(strlen(complex_chunk5) == packet->addBuffer(complex_chunk5, strlen(complex_chunk5)));
	CPPUNIT_ASSERT(packet->getDataSize() == 400);
	CPPUNIT_ASSERT(packet->isComplete() == true);

	CPPUNIT_ASSERT(strlen(chunk1) == packet->addBuffer(chunk1, strlen(chunk1)));
	CPPUNIT_ASSERT(strlen(chunk2) == packet->addBuffer(chunk2, strlen(chunk2)));
	CPPUNIT_ASSERT(strlen(chunk3) == packet->addBuffer(chunk3, strlen(chunk3)));
	CPPUNIT_ASSERT(strlen(chunk4) == packet->addBuffer(chunk4, strlen(chunk4)));
	CPPUNIT_ASSERT(strlen(chunk5) == packet->addBuffer(chunk5, strlen(chunk5)));
	CPPUNIT_ASSERT(strlen(chunk6) == packet->addBuffer(chunk6, strlen(chunk6)));
	HTTPPacket *p = packet->detachNext();
	delete packet;
	CPPUNIT_ASSERT(p->getDataSize() == 200);
	delete p;
	} 
}

void HTTPPacketTest::testAddSeriesPacket() {
	{
	// 添加一个连续的
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(series1) == packet->addBuffer(series1, strlen(series1)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series2) == packet->addBuffer(series2, strlen(series2)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series3) == packet->addBuffer(series3, strlen(series3)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series4) == packet->addBuffer(series4, strlen(series4)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series5) == packet->addBuffer(series5, strlen(series5)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series6) == packet->addBuffer(series5, strlen(series6)));
	CPPUNIT_ASSERT(true == packet->isComplete());
	CPPUNIT_ASSERT(packet->getDataSize() == 234);
	HTTPPacket *p = packet->detachNext();
	CPPUNIT_ASSERT(p == NULL);
	delete packet;
	}
}

void HTTPPacketTest::testAddSinglePacket() {
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(packet1) == packet->addBuffer(packet1, strlen(packet1)));
	CPPUNIT_ASSERT(strlen(packet2) == packet->addBuffer(packet2, strlen(packet2)));
	CPPUNIT_ASSERT(strlen(packet3) == packet->addBuffer(packet3, strlen(packet3)));

	HTTPPacket *p2 = packet->detachNext();
	CPPUNIT_ASSERT(packet->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	delete packet;

	HTTPPacket *p3 = p2->detachNext();
	CPPUNIT_ASSERT(p2->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_GIF);
	delete p2;

	CPPUNIT_ASSERT(NULL == p3->detachNext());
	CPPUNIT_ASSERT(p3->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_JPG);
	delete p3;

	{
	//=========================================
	// 测试添加非HTTP协议的包
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(packet1) == packet->addBuffer(packet1, strlen(packet1)));
	CPPUNIT_ASSERT(strlen(packet2) == packet->addBuffer(packet2, strlen(packet2)));
	CPPUNIT_ASSERT(strlen(packet3) == packet->addBuffer(packet3, strlen(packet3)));
	CPPUNIT_ASSERT(0 == packet->addBuffer(packet5, strlen(packet5)));
	CPPUNIT_ASSERT(strlen(packet3) == packet->addBuffer(packet3, strlen(packet3)));

	HTTPPacket *p2 = packet->detachNext();
	CPPUNIT_ASSERT(packet->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	delete packet;

	HTTPPacket *p3 = p2->detachNext();
	CPPUNIT_ASSERT(p2->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_GIF);
	delete p2;

	HTTPPacket *p4 = p3->detachNext();
	CPPUNIT_ASSERT(p3->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_JPG);
	delete p3;
	// 由于添加了两次包
	CPPUNIT_ASSERT(NULL == p4->detachNext());
	CPPUNIT_ASSERT(p4->getContentType()==HTTP_RESPONSE_HEADER::CONTYPE_JPG);
	delete p4;
	}
}

void HTTPPacketTest::testHTTPHeaderParsed() {
	// 测试头部解析是否正确
	HTTP_RESPONSE_HEADER header1;
	header1.parseHeader(packet1, strlen(packet1));
	CPPUNIT_ASSERT(header1.isChunk()== false);
	CPPUNIT_ASSERT(header1.getContentType()== HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	CPPUNIT_ASSERT(header1.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_CLOSE);
	CPPUNIT_ASSERT(header1.getContentLength() == 682);
	CPPUNIT_ASSERT(header1.getResponseCode() == 302);

	HTTP_RESPONSE_HEADER header2;
	header2.parseHeader(packet2, strlen(packet2));
	CPPUNIT_ASSERT(header2.isChunk()== false);
	CPPUNIT_ASSERT(header2.getContentType()== HTTP_RESPONSE_HEADER::CONTYPE_GIF);
	CPPUNIT_ASSERT(header2.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE);
	CPPUNIT_ASSERT(header2.getContentLength() == 234);
	CPPUNIT_ASSERT(header2.getResponseCode() == 302);

	HTTP_RESPONSE_HEADER header3;
	header3.parseHeader(packet3, strlen(packet3));
	CPPUNIT_ASSERT(header3.isChunk()== false);
	CPPUNIT_ASSERT(header3.getContentType()== HTTP_RESPONSE_HEADER::CONTYPE_JPG);
	CPPUNIT_ASSERT(header3.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_CLOSE);
	CPPUNIT_ASSERT(header3.getContentLength() == 62);
	CPPUNIT_ASSERT(header3.getResponseCode() == 302);

	HTTP_RESPONSE_HEADER header4;
	header4.parseHeader(packet4, strlen(packet4));
	CPPUNIT_ASSERT(header4.getContentType()== HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	CPPUNIT_ASSERT(header4.getConnectionState()== HTTP_RESPONSE_HEADER::NO_DESIGNATION);
	CPPUNIT_ASSERT(header4.isChunk()== true);
	CPPUNIT_ASSERT(header4.getResponseCode() == 200);

	HTTP_RESPONSE_HEADER header6;
	header6.parseHeader(packet6, strlen(packet4));
	CPPUNIT_ASSERT(header6.getContentType()== HTTP_RESPONSE_HEADER::CONTYPE_HTML);
	CPPUNIT_ASSERT(header6.getContentLength()== 3);
	CPPUNIT_ASSERT(header6.isChunk()== false);
	CPPUNIT_ASSERT(header6.getResponseCode() == 200);
}