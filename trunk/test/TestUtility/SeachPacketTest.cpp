#include "StdAfx.h"
#include ".\seachpackettest.h"
#include <utility\SeachPacket.h>
#include <utility\httprequestPacket.h>

SeachPacketTest::SeachPacketTest(void) 
{
}

SeachPacketTest::~SeachPacketTest(void) {
}

void SeachPacketTest::getContentTest() {
	{
	char * oper = "/s?wd=ddddddddddddddddddd HTTP/1.1";
	char * host_name = "www.baidu.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT( 0 == strcmp("ddddddddddddddddddd", result));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
	}

	{
	char * oper = "/search?p=ddddddddddddddd&fr=yfp-t-103&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1";
	char * host_name = "search.yahoo.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT( 0 == strcmp("ddddddddddddddd", result));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}

	{
	// 对于google来说， /search才是开头
	// 这也不是一个正常的search
	char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
	char * host_name = "www.google.com";

	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 == packet.parse(oper, host_name));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	}

	{
	// 对于google来说， /search才是开头
	char * oper = "/search?hl=en&q=aaaaaaaaaaaa&btnG=Google+Search&aq=f&oq= HTTP/1.1";
	char * host_name = "www.google.com";

	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}

	{
	// 对于google来说， /search才是开头
	char * oper = "/search?hl=en&q=aaaaaaaaaaaa&btnG=Google+Search&aq=f&oq= HTTP/1.1";
	char * host_name = "www.baidu.com";

	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 == packet.parse(oper, host_name));
	}

	{
	char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
	char * host_name = "www.baidu.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT( 0 == strcmp("hhhhhhhhhhhhhhhhhhhhhh", result));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
	}

	{
	// 次测试用例的主机地址错误
	char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
	char * host_name = "c.baidu.com";
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 == packet.parse(oper, host_name));
	}
}