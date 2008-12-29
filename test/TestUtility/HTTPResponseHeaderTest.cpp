#include "StdAfx.h"
#include ".\HTTPResponseHeaderTest .h"
#include <utility\HttpPacket.h>

using namespace CPPUNIT_NS;

HTTPRequestHeaderTest::HTTPRequestHeaderTest(void)
{
}

HTTPRequestHeaderTest::~HTTPRequestHeaderTest(void)
{
}

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

void HTTPRequestHeaderTest::testHTTPHeaderParsed() {
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
	const char * p = header2.getHeaderLine();
	CPPUNIT_ASSERT(0 == strcmp(header2.getDate(), "Thu, 24 Apr 2008 02:37:48 GMT"));
	CPPUNIT_ASSERT(0 == strcmp(header2.getHeaderLine(), "HTTP/1.1 302 Found"));
	CPPUNIT_ASSERT(0 == strlen(header2.getServer()));

	HTTP_RESPONSE_HEADER header3;
	header3.parseHeader(packet3, (int)strlen(packet3));
	CPPUNIT_ASSERT(header3.isChunk()== false);
	CPPUNIT_ASSERT(header3.getContentType()== CONTYPE_JPG);
	CPPUNIT_ASSERT(header3.getConnectionState()== HTTP_RESPONSE_HEADER::CONNECT_CLOSE);
	CPPUNIT_ASSERT(header3.getContentLength() == 62);
	CPPUNIT_ASSERT(header3.getResponseCode() == 302);
	CPPUNIT_ASSERT(header3.existContent() == true);
	CPPUNIT_ASSERT(0 == strlen(header3.getDate()));

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