#include "StdAfx.h"
#include ".\httprequestpackettest.h"
#include <utility\httprequestpacket.h>
#include <utility\protocolpacket.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


// 一个非法的HTTP包
void NoteHTTPRequest() {
	{
	HTTPRequestPacket request_packet;
	char * packet = "8";
 	int x = (int)request_packet.parsePacket(packet, (int)strlen(packet));
	BOOST_ASSERT(0 == x);
	}
}


void parseMultiPacket() {
	{
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\n"
	"Host: d1.sina.com.cn\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\n"
	"Connection: keep-alive\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\n";
	WSABUF wsabuf[1];
	wsabuf[0].buf = packet;
	wsabuf[0].len = (u_long)strlen(packet);

	// 测试解析后的可识别的项数
	HTTPRequestPacket request_packet;
	const int item_count = request_packet.parsePacket(wsabuf, 1);
	BOOST_ASSERT(item_count == 4);
	BOOST_ASSERT(request_packet.openPage() == true);

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getMainHostName(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("sina", buffer) == 0);
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("d1.sina.com.cn", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);

	}

	{
	char * packet1 = "POST HTTP/1.1\r\n"
	"Host: www.google.com\r\n";
	char * packet2 = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\n"
	"Connection: keep-alive\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\n";
	WSABUF wsabuf[2];
	wsabuf[0].buf = packet1;
	wsabuf[0].len = (u_long)strlen(packet1);
	wsabuf[1].buf = packet2;
	wsabuf[1].len = (u_long)strlen(packet2);

	// 测试解析后的可识别的项数
	HTTPRequestPacket request_packet;
	const int item_count = request_packet.parsePacket(wsabuf, 2);
	BOOST_ASSERT(item_count == 4);
	BOOST_ASSERT(request_packet.openPage() == false);

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getMainHostName(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("google", buffer) == 0);
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("www.google.com", buffer) == 0);


	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);

	}
}

void miscTest() {
	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\n"
	"Host: seach.google.com\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\n"
	"Connection: keep-alive\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\n";

	// 测试解析后的可识别的项数
 	const int item_count = request_packet.parsePacket(packet, (int)strlen(packet));
	const int buf_len = 5;
	char buffer[buf_len];
	request_packet.getGET(buffer, buf_len);
	BOOST_ASSERT(buffer[buf_len-1] == '\0');
	request_packet.getHost(buffer, buf_len);
	BOOST_ASSERT(buffer[buf_len-1] == '\0');
	request_packet.getMainHostName(buffer, buf_len);
	BOOST_ASSERT(buffer[buf_len-1] == '\0');
	request_packet.getUserAgent(buffer, buf_len);
	BOOST_ASSERT(buffer[buf_len-1] == '\0');
}

// test
void parsePacket() {
	{
	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\n"
	"Host: seach.google.com\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\n"
	"Connection: keep-alive\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\n";

	// 测试解析后的可识别的项数
 	const int item_count = request_packet.parsePacket(packet, (int)strlen(packet));
	BOOST_ASSERT(item_count == 4);
	BOOST_ASSERT(request_packet.openPage() == true);

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getMainHostName(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("google", buffer) == 0);
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("seach.google.com", buffer) == 0);


	BOOST_ASSERT(HTTPRequestPacket::HTTP_REQUEST_OPETYPE_GET == request_packet.getRequestType());
	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);


	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);
	}

	{
	HTTPRequestPacket request_packet;
	char * packet = "GET /iframe/gn/9/2007-04-28/17251.html HTTP/1.1\r\n"
	"Host: sAahh1.BAIDU.com\r\n"
	"Connection: keep-alive\r\n"
	"Referer: http://news.sina.com.cn/c/2008-09-04/202816233711.shtml\r\n"
	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF\r\n";

 	request_packet.parsePacket(packet, (int)strlen(packet));

	char buffer[HTTP_REQUEST_ITEM_MAX_LENGTH];
	request_packet.getMainHostName(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("baidu", buffer) == 0);
	request_packet.getHost(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("sAahh1.BAIDU.com", buffer) == 0);

	BOOST_ASSERT(HTTPRequestPacket::HTTP_REQUEST_OPETYPE_GET == request_packet.getRequestType());

	request_packet.getReferer(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("http://news.sina.com.cn/c/2008-09-04/202816233711.shtml", buffer) == 0);

	BOOST_ASSERT(0 != request_packet.getGET(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH));
	BOOST_ASSERT(strcmp("/iframe/gn/9/2007-04-28/17251.html HTTP/1.1", buffer) == 0);

	request_packet.getUserAgent(buffer, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT(strcmp("Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.16) Gecko/20080702 Firefox/2.0.0.16 GoogleToolbarFF", buffer) == 0);
	}
}