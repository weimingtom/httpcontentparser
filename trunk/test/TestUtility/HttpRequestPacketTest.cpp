#include "StdAfx.h"
#include ".\httprequestpackettest.h"
#include <utility\httprequestpacket.h>
#include <utility\protocolpacket.h>

HttpRequestPacketTest::HttpRequestPacketTest(void) {
}

HttpRequestPacketTest::~HttpRequestPacketTest(void) {
}

// 一个非法的HTTP包
void HttpRequestPacketTest::NoteHTTPRequest() {
	{
	HTTPRequestPacket request_packet;
	char * packet = "8";
 	int x = request_packet.parsePacket(packet, strlen(packet));
	CPPUNIT_ASSERT(0 == x);
	}
}


void HttpRequestPacketTest::parseMultiPacket() {
	{
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\r\n"
	"Host: d1.sina.com.cn\r\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\r\n"
	"Connection: keep-alive\r\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\r\n";
	WSABUF wsabuf[1];
	wsabuf[0].buf = packet;
	wsabuf[0].len = strlen(packet);

	HTTPRequestPacket request_packet;
	request_packet.parsePacket(wsabuf, 1);

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);

	}

		{
	char * packet1 = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\r\n"
	"Host: d1.sina.com.cn\r\r\n";
	char * packet2 = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\r\n"
	"Connection: keep-alive\r\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\r\n";
	WSABUF wsabuf[2];
	wsabuf[0].buf = packet1;
	wsabuf[0].len = strlen(packet1);
	wsabuf[1].buf = packet2;
	wsabuf[1].len = strlen(packet2);

	HTTPRequestPacket request_packet;
	request_packet.parsePacket(wsabuf, 2);

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);

	}
}


// test
void HttpRequestPacketTest::parsePacket() {
	{
	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\r\n"
	"Host: d1.sina.com.cn\r\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\r\n"
	"Connection: keep-alive\r\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\r\n";

 	request_packet.parsePacket(packet, strlen(packet));
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);
	}

	{
	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\r\n"
	"Host: d1.sina.com.cn\r\r\n"
	"Connection: keep-alive\r\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\r\n";

 	request_packet.parsePacket(packet, strlen(packet));
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);
	}
}