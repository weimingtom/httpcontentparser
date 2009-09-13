#include "StdAfx.h"
#include ".\httppackettest.h"
#include <utility\HttpPacket.h>
#include <utility\protocolpacket.h>
#include <webcontenttype.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

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


void testNoLengthSepecified() {
	//const char data1[] = "HTTP/1.1 200 OK\r\n"
	//	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	//	"Content-Type: image/gif\r\n"
	//	"Age: 220737\r\n"
	//	"Connection: keep-alive\r\n\r\n12345";

	//const char data2[] = "";
	//HTTPPacket *packet = new HTTPPacket;
	//packet->addBuffer(data1, strlen(data1));
	//packet->addBuffer(data2, strlen(data2));
	//BOOST_ASSERT(packet->isComplete() == true);
	//const int len = packet->getDataSize();
	//BOOST_ASSERT(len == 5);
	//delete packet;
}



void testSeriesPacket() {
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

	int result;
	HTTPPacket *packet = new HTTPPacket;
	int bytes1;
	result = packet->addBuffer(packet1, (int)strlen(packet1), &bytes1);
	BOOST_ASSERT (0 == result);
	BOOST_ASSERT(true == packet->isComplete());
	const char * packet2 = &(packet1[bytes1]);
	BOOST_ASSERT(packet2 == strstr(packet2, "HTTP"));
	BOOST_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	int bytes2;
	result = packet->addBuffer(packet2, (int)strlen(packet2), &bytes2);
	BOOST_ASSERT (0 == result);
	BOOST_ASSERT(true == packet->isComplete());
	const char * packet3 = &(packet2[bytes2]);
	BOOST_ASSERT(packet3 == strstr(packet3, "HTTP"));
	BOOST_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	int bytes3;
	result = packet->addBuffer(packet3, (int)strlen(packet3), &bytes3);
	BOOST_ASSERT (0 == result);
	BOOST_ASSERT(true == packet->isComplete());
	const char * packet4 = &(packet3[bytes3]);
	BOOST_ASSERT(packet->getContentType()==CONTYPE_HTML);
	delete packet;

	packet = new HTTPPacket;
	int bytes4;
	result = packet->addBuffer(packet4, (int)strlen(packet4), &bytes4);
	// assert (0 == result);
	BOOST_ASSERT(bytes4 == 0);
	BOOST_ASSERT(true == packet->isComplete());
    delete packet;
}

// �����ܵ�һ�������HTTP��ʱ
// packet->addBuffer�᷵��һ��-1
// ���Ҹð��ᱻ���Ϊһ���Ѿ���ɵİ���
void testWrongHeader() {
	HTTPPacket *packet = new HTTPPacket;
	char buffer1[] = "HTTP"; 
	char buffer2[] = "HTTP aidji8vz2\r\noaijdfoin\r\n\r\n";
	int length;

	// ����ʧ�ܣ� ��֪����Ǻ���
	BOOST_ASSERT(-1 == (int)packet->addBuffer(buffer1, (int)strlen(buffer1), &length));
	BOOST_ASSERT(packet->isComplete() == true);	// ��ʱ����Ϊ��ɵ�
	// BOOST_ASSERT(0 == packet->addBuffer(buffer2, strlen(buffer2)));

    delete packet;
}

// ���Ի�ȡԭʼ���ݰ�
void testRawPacket() {
	HTTPPacket *packet = new HTTPPacket;
	int added_length;
	BOOST_ASSERT(0 == packet->addBuffer(chunk1, (int)strlen(chunk1), &added_length));
	BOOST_ASSERT((int)strlen(chunk1) == added_length);

  	BOOST_ASSERT(0 == packet->addBuffer(chunk2, (int)strlen(chunk2), &added_length));
	BOOST_ASSERT((int)strlen(chunk2) == added_length);

	BOOST_ASSERT(0== packet->addBuffer(chunk3, (int)strlen(chunk3), &added_length));
	BOOST_ASSERT((int)strlen(chunk3) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk4, (int)strlen(chunk4), &added_length));
	BOOST_ASSERT((int)strlen(chunk4) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk5, (int)strlen(chunk5), &added_length));
	BOOST_ASSERT((int)strlen(chunk5) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk6, (int)strlen(chunk6), &added_length));
	BOOST_ASSERT((int)strlen(chunk6) == added_length);

	const int buf_len = 1024 * 64;
	char buffer[buf_len];

	ProtocolPacket<HTTP_PACKET_SIZE> *raw_packet1 = packet->getRawPacket();
	int len1 = raw_packet1->read(buffer, buf_len);
	buffer[len1+1] = '\0';
	const int total_length  = (int)(strlen(chunk1) + strlen(chunk2) + strlen(chunk3) +
		strlen(chunk4) + strlen(chunk5) + strlen(chunk6));
	BOOST_ASSERT(len1 == total_length);
	
	delete packet;
}

// ����һ��chunk����ֻ�г���Ϊ0��һ���ε�ʱ��
void testZeroChunk() {
	char data1[] = "HTTP/1.1 302 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n"
	"Transfer-Encoding: chunked\r\n\r\n"
	"0\r\n\r\n";

	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(data1, (int)strlen(data1), &added_length));
	BOOST_ASSERT((int)strlen(data1) == added_length);
	BOOST_ASSERT(packet->isComplete() == true);
    delete packet;
}

// ���Ա��뷽ʽΪchunk��HTTP��
void testChunk() {
	{ 
	// ���һ��������
	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(chunk1, (int)strlen(chunk1), &added_length));
	BOOST_ASSERT((int)strlen(chunk1) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(chunk2, (int)strlen(chunk2), &added_length));
	BOOST_ASSERT((int)strlen(chunk2) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(chunk3, (int)strlen(chunk3), &added_length));
	BOOST_ASSERT((int)strlen(chunk3) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32 * 2);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(chunk4, (int)strlen(chunk4), &added_length));
	BOOST_ASSERT((int)strlen(chunk4) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32 * 3);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(chunk5, (int)strlen(chunk5), &added_length));
	BOOST_ASSERT((int)strlen(chunk5) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32 * 4);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(chunk6, (int)strlen(chunk6), &added_length));
	BOOST_ASSERT((int)strlen(chunk6) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 200);
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;
	}

	{
	int added_length;
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
	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk1, (int)strlen(complex_chunk1), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk1) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk2, (int)strlen(complex_chunk2), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk2) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk3, (int)strlen(complex_chunk3), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk3) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 300);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk4, (int)strlen(complex_chunk4), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk4) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk5, (int)strlen(complex_chunk5), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk5) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 400);
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;

	packet = new HTTPPacket;
	int expected_length;
	BOOST_ASSERT(0 == packet->addBuffer(chunk1, (int)strlen(chunk1), &expected_length));
	BOOST_ASSERT((int)strlen(chunk1) == expected_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk2, (int)strlen(chunk2), &expected_length));
	BOOST_ASSERT((int)strlen(chunk2) == expected_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk3, (int)strlen(chunk3), &expected_length));
	BOOST_ASSERT((int)strlen(chunk3) == expected_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk4, (int)strlen(chunk4), &expected_length));
	BOOST_ASSERT((int)strlen(chunk4) == expected_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk5, (int)strlen(chunk5), &expected_length));
	BOOST_ASSERT((int)strlen(chunk5) == expected_length);

	BOOST_ASSERT(0 == packet->addBuffer(chunk6, (int)strlen(chunk6), &expected_length));
	BOOST_ASSERT((int)strlen(chunk6) == expected_length);

	delete packet;
	} 
}

void testAddSeriesPacket() {
	{
	int added_length;
	// ���һ��������
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(series1, (int)strlen(series1), &added_length));
	BOOST_ASSERT((int)strlen(series1) == added_length);
	BOOST_ASSERT(false == packet->isComplete());

	BOOST_ASSERT(0 == packet->addBuffer(series2, (int)strlen(series2), &added_length));
	BOOST_ASSERT(false == packet->isComplete());
	BOOST_ASSERT((int)strlen(series2) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(series3, (int)strlen(series3), &added_length));
	BOOST_ASSERT(false == packet->isComplete());
	BOOST_ASSERT((int)strlen(series3) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(series4, (int)strlen(series4), &added_length));
	BOOST_ASSERT(false == packet->isComplete());
	BOOST_ASSERT((int)strlen(series4) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(series5, (int)strlen(series5), &added_length));
	BOOST_ASSERT(false == packet->isComplete());
	BOOST_ASSERT((int)strlen(series5) == added_length);

	BOOST_ASSERT(0 == packet->addBuffer(series5, (int)strlen(series6), &added_length));
	BOOST_ASSERT(true == packet->isComplete());
	BOOST_ASSERT((int)strlen(series6) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 234);
	delete packet;
	}
}

void testAddSinglePacket() {
	int added_length;
	HTTPPacket *httppacket1 = new HTTPPacket;
	BOOST_ASSERT(0 == httppacket1->addBuffer(packet1, (int)strlen(packet1), &added_length));
	BOOST_ASSERT((int)strlen(packet1) == added_length);

	HTTPPacket *httppacket2 = new HTTPPacket;
	BOOST_ASSERT(0 == httppacket2->addBuffer(packet2, (int)strlen(packet2), &added_length));
	BOOST_ASSERT((int)strlen(packet2) == added_length);

	HTTPPacket *httppacket3 = new HTTPPacket;
	BOOST_ASSERT(0 == httppacket3->addBuffer(packet3, (int)strlen(packet3), &added_length));
	BOOST_ASSERT((int)strlen(packet3) == added_length);

	BOOST_ASSERT(httppacket1->getContentType()==CONTYPE_HTML);
	BOOST_ASSERT(httppacket2->getContentType()==CONTYPE_GIF);
	BOOST_ASSERT(httppacket3->getContentType()==CONTYPE_JPG);
	delete httppacket1;
	delete httppacket2;
	delete httppacket3;
}


// ����û�����ݵİ�
// ���� 204�� 304�� 1**�İ��� ����û������
void testNoContentHeader() {
	char data1[] = "HTTP/1.1 304 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header1;
	header1.parseHeader(data1, (int)strlen(data1));
	BOOST_ASSERT(header1.getResponseCode() == 304);
	BOOST_ASSERT(header1.existContent() == false);

	char data2[] = "HTTP/1.1 204 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header2;
	header2.parseHeader(data2, (int)strlen(data2));
	BOOST_ASSERT(header2.getResponseCode() == 204);
	BOOST_ASSERT(header2.existContent() == false);

	char data3[] = "HTTP/1.1 104 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header3;
	header3.parseHeader(data3, (int)strlen(data3));
	BOOST_ASSERT(header3.getResponseCode() == 104);
	BOOST_ASSERT(header3.existContent() == false);

	char data4[] = "HTTP/1.1 100 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n";
	HTTP_RESPONSE_HEADER header4;
	header4.parseHeader(data4, (int)strlen(data4));
	BOOST_ASSERT(header4.getResponseCode() == 100);
	BOOST_ASSERT(header4.existContent() == false);

	char data5[] = "HTTP/1.1 193 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header5;
	header5.parseHeader(data5, (int)strlen(data5));
	BOOST_ASSERT(header5.getResponseCode() == 193);
	BOOST_ASSERT(header5.existContent() == false);

	char data6[] = "HTTP/1.1 293 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n";
	HTTP_RESPONSE_HEADER header6;
	header6.parseHeader(data6, (int)strlen(data6));
	BOOST_ASSERT(header6.getResponseCode() == 293);
	BOOST_ASSERT(header6.existContent() == true);
}

// ���Գ���Ϊ0�İ�
void testZeorLengthPacket() {
	const char data[] = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n"
		"Cache-Control: public,max-age=600\r\n"
		"Date: Tue, 15 Jul 2008 15:06:40 GMT\r\n"
		"Server: TrustRank Frontend\r\n"
		"Content-Length: 0\r\n\r\n";
		
	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(data, (int)strlen(data), &added_length));
	BOOST_ASSERT((int)strlen(data) == added_length);
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;
}

void testConnectionState() {
	const char p1[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: close\r\n\r\n0\r\n\r\n";

	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(p1, (int)strlen(p1), &added_length));
	BOOST_ASSERT((int)strlen(p1) == added_length);
	BOOST_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_CLOSE == packet->getHeader()->getConnectionState());
	delete packet;

	const char p2[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: keep-alive\r\n\r\n0\r\n\r\n";

	packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(p2, (int)strlen(p2), &added_length));
	BOOST_ASSERT((int)strlen(p2) == added_length);
	BOOST_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE == packet->getHeader()->getConnectionState());
	delete packet;
}

void testNoContentChunk() {
	const char complex_chunk1[] = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Type: image/gif\r\n"
		"Age: 220737\r\n"
		"Transfer-Encoding: chunked\r\n"
		"Connection: keep-alive\r\n\r\n0\r\n\r\n";

	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk1,(int)strlen(complex_chunk1), &added_length));
	BOOST_ASSERT((int)strlen(complex_chunk1) == added_length);
	BOOST_ASSERT(HTTP_RESPONSE_HEADER::CONNECT_KEEP_ALIVE == packet->getHeader()->getConnectionState());
	BOOST_ASSERT(true == packet->isComplete());
	delete packet;
}

void testNoContentPacket() {
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
	BOOST_ASSERT(header1.isChunk()== false);
	BOOST_ASSERT(header1.getResponseCode() == 304);

	int added_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(no_content, (int)strlen(no_content), &added_length));
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;
}

//  ��һ����Ϊ������ʱ���յ�һ������Ϊ0�İ�
void testAdd0LengthPacket() {
	int added_length;
	{
	const char length_specified[] = "HTTP/1.1 302 Found\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Length: 62\r\n"
		"Content-Type: image/jpeg\r\n"
		"Connection: keep-alive\r\n\r\n"
		"123456789012";
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(length_specified, (int)strlen(length_specified), &added_length));
	BOOST_ASSERT(strlen(length_specified) == added_length);
	BOOST_ASSERT(packet->isComplete() == false);
	BOOST_ASSERT(0 == packet->addBuffer(length_specified, 0, &added_length));
	BOOST_ASSERT(0 == added_length);
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;
	}

	{
	// ����һ��closed�İ��� ���ۺ�ʱ��Ӧ��s
	// ��һ���̶����Ȱ��м�һ��0���Ȱ�
	const char length_specified[] = "HTTP/1.1 302 Found\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Content-Length: 62\r\n"
		"Content-Type: image/jpeg\r\n"
		"Connection: close\r\n\r\n"
		"123456789012";
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(length_specified, (int)strlen(length_specified), &added_length));
	BOOST_ASSERT(strlen(length_specified) == added_length);
	BOOST_ASSERT(packet->isComplete() == false);
	BOOST_ASSERT(0 == packet->addBuffer(length_specified, 0, &added_length));
	BOOST_ASSERT(0 == added_length);
	BOOST_ASSERT(packet->isComplete() == true);
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
	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk1, (int)strlen(complex_chunk1), &added_length));
	BOOST_ASSERT(strlen(complex_chunk1) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk2, (int)strlen(complex_chunk2), &added_length));
	BOOST_ASSERT(strlen(complex_chunk2) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 0x32);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk3, (int)strlen(complex_chunk3), &added_length));
	BOOST_ASSERT(strlen(complex_chunk3) == added_length);
	BOOST_ASSERT(packet->getDataSize() == 300);
	BOOST_ASSERT(packet->isComplete() == false);

	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk4, (int)strlen(complex_chunk4), &added_length));
	BOOST_ASSERT(strlen(complex_chunk4) == added_length);

	// ����һ������Ϊ0�İ�
	BOOST_ASSERT(0 == packet->addBuffer(complex_chunk5, 0, &added_length));
	BOOST_ASSERT(0 == added_length);
	BOOST_ASSERT(packet->isComplete() == true);
	delete packet;
	}
}

void testActuallyPacket() {
	const char acutal_data[] = "HTTP/1.0 200 OK\r\n"
				"Date: Fri, 26 Dec 2008 07:14:39 GMT\r\n"
				"Server: Apache/2.0.63 (Unix)\r\n"
				"Last-Modified: Fri, 26 Dec 2008 07:12:29 GMT\r\n"
				"Accept-Ranges: bytes\r\n"
				"X-Powered-By: mod_xlayout_jh/0.0.1vhs.markII.remix\r\n"
				"Cache-Control: max-age=60\r\n"
				"Expires: Fri, 26 Dec 2008 07:15:39 GMT\r\n"
				"Vary: Accept-Encoding\r\n"
				"Content-Encoding: gzip\r\n"
				"X-UA-Compatible: IE=EmulateIE7\r\n"
				"Content-Type: text/html\r\n"
				"X-Cache: MISS from xd33-95.HP08040034.sina.com.cn\r\n"
				"Via: 1.0 xd33-95.HP08040034.sina.com.cn:80 (squid/2.6.STABLE13)\r\n"
				"Connection: close\r\n\r\n"
				"kkdkdkdkdkdkdk";
	
	int actual_length;
	HTTPPacket *packet = new HTTPPacket;
	BOOST_ASSERT(0 == packet->addBuffer(acutal_data, strlen(acutal_data), &actual_length));
    delete packet;
}