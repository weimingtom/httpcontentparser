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
	char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
	char * host_name = "google.com";

	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 == packet.parse(oper, host_name));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}

	{
	char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
	char * host_name = "baidu.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT( 0 == strcmp("hhhhhhhhhhhhhhhhhhhhhh", result));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
	}

	{
	char * oper = "/search?p=hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh&y=Search&fr=yfp-t-501&ei=UTF-8&fp_ip=CN&rd=r1&meta=vc%3Dcn HTTP/1.1";
	char * host_name = "yahoo.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	CPPUNIT_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	CPPUNIT_ASSERT( 0 == strcmp("hhhhhhhhhhhhhhhhhhhhhh", result));
	CPPUNIT_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}
}