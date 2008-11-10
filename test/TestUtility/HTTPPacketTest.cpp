#include "StdAfx.h"
#include ".\httppackettest.h"
#include <utility\HttpPacket.h>
#include <utility\protocolpacket.h>
#include <webcontenttype.h>


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
"Connection: close\r\n\r\n"
"12345678901234567890123456789012345678901234567890"
"123456789012";

const char packet4[] = "HTTP/1.1 200 OK\r\n"
"Cache-Control: private, max-age=0\r\n"
"Date: Fri, 13 Jun 2008 13:59:34 GMT\r\n"
"Expires: -1\r\n"
"Content-Type: text/html; charset=UTF-8\r\n"
"Content-Encoding: gzip\r\n"
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

void HTTPPacketTest::testNoLengthSepecified() {
	//const char data1[] = "HTTP/1.1 200 OK\r\n"
	//	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	//	"Content-Type: image/gif\r\n"
	//	"Age: 220737\r\n"
	//	"Connection: keep-alive\r\n\r\n12345";

	//const char data2[] = "";
	//HTTPPacket *packet = new HTTPPacket;
	//packet->addBuffer(data1, strlen(data1));
	//packet->addBuffer(data2, strlen(data2));
	//CPPUNIT_ASSERT(packet->isComplete() == true);
	//const int len = packet->getDataSize();
	//CPPUNIT_ASSERT(len == 5);
	//delete packet;
}



void HTTPPacketTest::testSeriesPacket() {
	const char packet1[] = 	"HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Content-Length: 2\r\n"
	"Content-Type: text/html\r\n"
	"Age: 220737\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: keep-alive\r\n\r\n"
	"aa"
	"HTTP/1.1 200 OK\r\n"
	"Content-Length: 3\r\n"
	"Content-Type: text/html\r\n"
	"Age: 220737\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: keep-alive\r\n\r\n"
	"aaa"
	"HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Content-Length: 6\r\n"
	"Content-Type: text/html\r\n"
	"X-Cache: HIT from 168479083.sohu.com\r\n"
	"Connection: keep-alive\r\n\r\n"
	"aaaaaa";

	HTTPPacket *packet = new HTTPPacket;
	const int bytes1 = (int)packet->addBuffer(packet1, (int)strlen(packet1));
	CPPUNIT_ASSERT(true == packet->isComplete());
	const char * packet2 = &(packet1[bytes1]);
	CPPUNIT_ASSERT(packet2 == strstr(packet2, "HTTP"));
	CPPUNIT_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	const int bytes2 = (int)packet->addBuffer(packet2, (int)strlen(packet2));
	CPPUNIT_ASSERT(true == packet->isComplete());
	const char * packet3 = &(packet2[bytes2]);
	CPPUNIT_ASSERT(packet3 == strstr(packet3, "HTTP"));
	CPPUNIT_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	const int bytes3 = (int)packet->addBuffer(packet3, (int)strlen(packet3));
	CPPUNIT_ASSERT(true == packet->isComplete());
	const char * packet4 = &(packet3[bytes3]);
	CPPUNIT_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	const int bytes4 = packet->addBuffer(packet4, (int)strlen(packet4));
	CPPUNIT_ASSERT(bytes4 == 0);
	CPPUNIT_ASSERT(true == packet->isComplete());
}

void HTTPPacketTest::testWrongHeader() {
	HTTPPacket *packet = new HTTPPacket;
	char buffer1[] = "HTTP"; 
	char buffer2[] = "HTTP aidji8vz2\r\noaijdfoin\r\n\r\n";
	CPPUNIT_ASSERT(0 == (int)packet->addBuffer(buffer1, (int)strlen(buffer1)));
	// CPPUNIT_ASSERT(0 == packet->addBuffer(buffer2, strlen(buffer2)));
}

// 测试获取原始数据包
void HTTPPacketTest::testRawPacket() {
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT((int)strlen(chunk1) == packet->addBuffer(chunk1, (int)strlen(chunk1)));
	CPPUNIT_ASSERT((int)strlen(chunk2) == packet->addBuffer(chunk2, (int)strlen(chunk2)));
	CPPUNIT_ASSERT((int)strlen(chunk3) == packet->addBuffer(chunk3, (int)strlen(chunk3)));
	CPPUNIT_ASSERT((int)strlen(chunk4) == packet->addBuffer(chunk4, (int)strlen(chunk4)));
	CPPUNIT_ASSERT((int)strlen(chunk5) == packet->addBuffer(chunk5, (int)strlen(chunk5)));
	CPPUNIT_ASSERT((int)strlen(chunk6) == packet->addBuffer(chunk6, (int)strlen(chunk6)));

	const int buf_len = 1024 * 64;
	char buffer[buf_len];

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet1 = packet->getRawPacket();
	int len1 = raw_packet1->read(buffer, buf_len);
	buffer[len1+1] = '\0';
	const int total_length  = (int)(strlen(chunk1) + strlen(chunk2) + strlen(chunk3) +
		strlen(chunk4) + strlen(chunk5) + strlen(chunk6));
	CPPUNIT_ASSERT(len1 == total_length);
	
	delete packet;
}

// 对于一个chunk当他只有长度为0的一个段的时候
void HTTPPacketTest::testZeroChunk() {
	char data1[] = "HTTP/1.1 302 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n"
	"Transfer-Encoding: chunked\r\n\r\n"
	"0\r\n\r\n";

	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(data1) == packet->addBuffer(data1, (int)strlen(data1)));
	CPPUNIT_ASSERT(packet->isComplete() == true);
}

// 测试编码方式为chunk的HTTP包
void HTTPPacketTest::testChunk() {
	{ 
	// 添加一个连续的
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT((int)strlen(chunk1) == packet->addBuffer(chunk1, (int)strlen(chunk1)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(chunk2) == packet->addBuffer(chunk2, (int)strlen(chunk2)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(chunk3) == packet->addBuffer(chunk3, (int)strlen(chunk3)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 2);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(chunk4) == packet->addBuffer(chunk4, (int)strlen(chunk4)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 3);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(chunk5) == packet->addBuffer(chunk5, (int)strlen(chunk5)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32 * 4);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(chunk6) == packet->addBuffer(chunk6, (int)strlen(chunk6)));
	CPPUNIT_ASSERT(packet->getDataSize() == 200);
	CPPUNIT_ASSERT(packet->isComplete() == true);
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
	CPPUNIT_ASSERT((int)strlen(complex_chunk1) == packet->addBuffer(complex_chunk1, (int)strlen(complex_chunk1)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk2) == packet->addBuffer(complex_chunk2, (int)strlen(complex_chunk2)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk3) == packet->addBuffer(complex_chunk3, (int)strlen(complex_chunk3)));
	CPPUNIT_ASSERT(packet->getDataSize() == 300);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk4) == packet->addBuffer(complex_chunk4, (int)strlen(complex_chunk4)));
	CPPUNIT_ASSERT((int)strlen(complex_chunk5) == packet->addBuffer(complex_chunk5, (int)strlen(complex_chunk5)));
	CPPUNIT_ASSERT(packet->getDataSize() == 400);
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;

	packet = new HTTPPacket;
	CPPUNIT_ASSERT((int)strlen(chunk1) == packet->addBuffer(chunk1, (int)strlen(chunk1)));
	CPPUNIT_ASSERT((int)strlen(chunk2) == packet->addBuffer(chunk2, (int)strlen(chunk2)));
	CPPUNIT_ASSERT((int)strlen(chunk3) == packet->addBuffer(chunk3, (int)strlen(chunk3)));
	CPPUNIT_ASSERT((int)strlen(chunk4) == packet->addBuffer(chunk4, (int)strlen(chunk4)));
	CPPUNIT_ASSERT((int)strlen(chunk5) == packet->addBuffer(chunk5, (int)strlen(chunk5)));
	CPPUNIT_ASSERT((int)strlen(chunk6) == packet->addBuffer(chunk6, (int)strlen(chunk6)));
	delete packet;
	} 
}

void HTTPPacketTest::testAddSeriesPacket() {
	{
	// 添加一个连续的
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(series1) == packet->addBuffer(series1, (int)strlen(series1)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series2) == packet->addBuffer(series2, (int)strlen(series2)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series3) == packet->addBuffer(series3, (int)strlen(series3)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series4) == packet->addBuffer(series4, (int)strlen(series4)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series5) == packet->addBuffer(series5, (int)strlen(series5)));
	CPPUNIT_ASSERT(false == packet->isComplete());
	CPPUNIT_ASSERT(strlen(series6) == packet->addBuffer(series5, (int)strlen(series6)));
	CPPUNIT_ASSERT(true == packet->isComplete());
	CPPUNIT_ASSERT(packet->getDataSize() == 234);
	delete packet;
	}
}

void HTTPPacketTest::testAddSinglePacket() {
	HTTPPacket *httppacket1 = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(packet1) == httppacket1->addBuffer(packet1, (int)strlen(packet1)));
	HTTPPacket *httppacket2 = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(packet2) == httppacket2->addBuffer(packet2, (int)strlen(packet2)));
	HTTPPacket *httppacket3 = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(packet3) == httppacket3->addBuffer(packet3, (int)strlen(packet3)));

	CPPUNIT_ASSERT(httppacket1->getContentType()==CONTYPE_HTML);
	CPPUNIT_ASSERT(httppacket2->getContentType()==CONTYPE_GIF);
	CPPUNIT_ASSERT(httppacket3->getContentType()==CONTYPE_JPG);
	delete httppacket1;
	delete httppacket2;
	delete httppacket3;
}

void HTTPPacketTest::testHTTPHeaderParsed() {
	// 测试头部解析是否正确
	HTTP_RESPONSE_HEADER header1;
	header1.parseHeader(packet1, (int)strlen(packet1));
	CPPUNIT_ASSERT(header1.isChunk()== false);
	CPPUNIT_ASSERT(header1.getContentType()== CONTYPE_HTML);
	CPPUNIT_ASSERT(header1.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_CLOSE);
	CPPUNIT_ASSERT(header1.getContentLength() == 682);
	CPPUNIT_ASSERT(header1.getResponseCode() == 302);
	CPPUNIT_ASSERT(header1.existContent() == true);

	HTTP_RESPONSE_HEADER header2;
	header2.parseHeader(packet2, (int)strlen(packet2));
	CPPUNIT_ASSERT(header2.isChunk()== false);
	CPPUNIT_ASSERT(header2.getContentType()==  CONTYPE_GIF);
	CPPUNIT_ASSERT(header2.getConnectionState()==  HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE);
	CPPUNIT_ASSERT(header2.getContentLength() == 234);
	CPPUNIT_ASSERT(header2.getResponseCode() == 302);
	CPPUNIT_ASSERT(header2.existContent() == true);

	HTTP_RESPONSE_HEADER header3;
	header3.parseHeader(packet3, (int)strlen(packet3));
	CPPUNIT_ASSERT(header3.isChunk()== false);
	CPPUNIT_ASSERT(header3.getContentType()== CONTYPE_JPG);
	CPPUNIT_ASSERT(header3.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_CLOSE);
	CPPUNIT_ASSERT(header3.getContentLength() == 62);
	CPPUNIT_ASSERT(header3.getResponseCode() == 302);
	CPPUNIT_ASSERT(header3.existContent() == true);

	HTTP_RESPONSE_HEADER header4;
	header4.parseHeader(packet4, (int)strlen(packet4));
	CPPUNIT_ASSERT(header4.getContentType()== CONTYPE_HTML);
	CPPUNIT_ASSERT(header4.getConnectionState()== HTTP_RESPONSE_HEADER::NO_DESIGNATION);
	CPPUNIT_ASSERT(header4.isChunk()== true);
	CPPUNIT_ASSERT(header4.getResponseCode() == 200);
	CPPUNIT_ASSERT(header4.existContent() == true);

	HTTP_RESPONSE_HEADER header6;
	header6.parseHeader(packet6, (int)strlen(packet4));
	CPPUNIT_ASSERT(header6.getContentType()== CONTYPE_HTML);
	CPPUNIT_ASSERT(header6.getContentLength()== 3);
	CPPUNIT_ASSERT(header6.isChunk()== false);
	CPPUNIT_ASSERT(header6.getResponseCode() == 200);
	CPPUNIT_ASSERT(header6.existContent() == true);
}

// 测试没有内容的包
// 对于 204， 304， 1**的包， 他们没有内容
void HTTPPacketTest::testNoContentHeader() {
	char data1[] = "HTTP/1.1 304 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header1;
	header1.parseHeader(data1, (int)strlen(data1));
	CPPUNIT_ASSERT(header1.getResponseCode() == 304);
	CPPUNIT_ASSERT(header1.existContent() == false);

	char data2[] = "HTTP/1.1 204 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header2;
	header2.parseHeader(data2, (int)strlen(data2));
	CPPUNIT_ASSERT(header2.getResponseCode() == 204);
	CPPUNIT_ASSERT(header2.existContent() == false);

	char data3[] = "HTTP/1.1 104 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header3;
	header3.parseHeader(data3, (int)strlen(data3));
	CPPUNIT_ASSERT(header3.getResponseCode() == 104);
	CPPUNIT_ASSERT(header3.existContent() == false);

	char data4[] = "HTTP/1.1 100 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n";
	HTTP_RESPONSE_HEADER header4;
	header4.parseHeader(data4, (int)strlen(data4));
	CPPUNIT_ASSERT(header4.getResponseCode() == 100);
	CPPUNIT_ASSERT(header4.existContent() == false);

	char data5[] = "HTTP/1.1 193 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header5;
	header5.parseHeader(data5, (int)strlen(data5));
	CPPUNIT_ASSERT(header5.getResponseCode() == 193);
	CPPUNIT_ASSERT(header5.existContent() == false);

	char data6[] = "HTTP/1.1 293 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header6;
	header6.parseHeader(data6, (int)strlen(data6));
	CPPUNIT_ASSERT(header6.getResponseCode() == 293);
	CPPUNIT_ASSERT(header6.existContent() == true);
}

// 测试长度为0的包
void HTTPPacketTest::testZeorLengthPacket() {
	const char data[] = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n"
		"Cache-Control: public,max-age=600\r\n"
		"Date: Tue, 15 Jul 2008 15:06:40 GMT\r\n"
		"Server: TrustRank Frontend\r\n"
		"Content-Length: 0\r\n\r\n";
		
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT((int)strlen(data) == packet->addBuffer(data, (int)strlen(data)));
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;
}

void HTTPPacketTest::testConnectionState() {
	const char p1[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: close\r\n\r\n0\r\n\r\n";

	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(p1) == packet->addBuffer(p1, (int)strlen(p1)));
	CPPUNIT_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_CLOSE == packet->getHeader()->getConnectionState());
	delete packet;

	const char p2[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: keep-alive\r\n\r\n0\r\n\r\n";

	packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(p2) == packet->addBuffer(p2, (int)strlen(p2)));
	CPPUNIT_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE == packet->getHeader()->getConnectionState());
	delete packet;
}

void HTTPPacketTest::testNoContentChunk() {
	const char complex_chunk1[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: keep-alive\r\n\r\n0\r\n\r\n";

	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(complex_chunk1) == packet->addBuffer(complex_chunk1,
		(int)strlen(complex_chunk1)));
	CPPUNIT_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE == packet->getHeader()->getConnectionState());
	CPPUNIT_ASSERT(true == packet->isComplete());
	delete packet;
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
	header1.parseHeader(no_content, (int)strlen(no_content));
	CPPUNIT_ASSERT(header1.isChunk()== false);
	CPPUNIT_ASSERT(header1.getResponseCode() == 304);

	HTTPPacket *packet = new HTTPPacket;
	packet->addBuffer(no_content, (int)strlen(no_content));
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;
}

//  在一个包为结束的时候收到一个长度为0的包
void HTTPPacketTest::testAdd0LengthPacket() {
	{
	const char length_specified[] = "HTTP/1.1 302 Found\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Length: 62\r\n"
		"Content-Type: image/jpeg\r\n"
		"Connection: keep-alive\r\n\r\n"
		"123456789012";
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(length_specified) == packet->addBuffer(length_specified, (int)strlen(length_specified)));
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(0 == packet->addBuffer(length_specified, 0));
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;
	}

	{
	// 对于一个closed的包， 无论何时都应该s
	// 在一个固定长度包中加一个0长度包
	const char length_specified[] = "HTTP/1.1 302 Found\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Length: 62\r\n"
		"Content-Type: image/jpeg\r\n"
		"Connection: close\r\n\r\n"
		"123456789012";
	HTTPPacket *packet = new HTTPPacket;
	CPPUNIT_ASSERT(strlen(length_specified) == packet->addBuffer(length_specified, (int)strlen(length_specified)));
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT(0 == packet->addBuffer(length_specified, 0));
	CPPUNIT_ASSERT(packet->isComplete() == false);
	delete packet;
	}

	{
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
	CPPUNIT_ASSERT((int)strlen(complex_chunk1) == packet->addBuffer(complex_chunk1, (int)strlen(complex_chunk1)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk2) == packet->addBuffer(complex_chunk2, (int)strlen(complex_chunk2)));
	CPPUNIT_ASSERT(packet->getDataSize() == 0x32);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk3) == packet->addBuffer(complex_chunk3, (int)strlen(complex_chunk3)));
	CPPUNIT_ASSERT(packet->getDataSize() == 300);
	CPPUNIT_ASSERT(packet->isComplete() == false);
	CPPUNIT_ASSERT((int)strlen(complex_chunk4) == packet->addBuffer(complex_chunk4, (int)strlen(complex_chunk4)));

	// 增加一个长度为0的包
	CPPUNIT_ASSERT(0 == packet->addBuffer(complex_chunk5, 0));
	CPPUNIT_ASSERT(packet->isComplete() == true);
	delete packet;
	}
}