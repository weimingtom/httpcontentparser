#include "StdAfx.h"
#include ".\httprequestpackettest.h"
#include <utility\httprequestpacket.h>
#include <utility\protocolpacket.h>

HttpRequestPacketTest::HttpRequestPacketTest(void) {
}

HttpRequestPacketTest::~HttpRequestPacketTest(void) {
}


// test
void HttpRequestPacketTest::parsePacket() {

	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1"
	"Host: d1.sina.com.cn"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF"
	"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
	"Accept-Language: en-us,en;q=0.5"
	"Accept-Encoding: gzip,deflate"
	"Accept-Charset: x-gbk,utf-8;q=0.7,*;q=0.7"
	"Keep-Alive: 300"
	"Connection: keep-alive"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml"
	"If-Modified-Since: Wed, 03 Sep 2008 10:57:29 GMT"
	"Cache-Control: max-age=0";

	request_packet.parsePacket(packet, strlen(packet));
	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);
}