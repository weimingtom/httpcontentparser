#include "StdAfx.h"
#include ".\serviceutilitytest.h"
#include <serviceUtility.h>
#include <utility/HTTPRequestPacket.h>

namespace {
};
ServiceutilityTest::ServiceutilityTest(void)
{
}

ServiceutilityTest::~ServiceutilityTest(void)
{
}

void ServiceutilityTest::TestCheckSeachRule() {
	{
	char * require = "GET /search?hl=en&q=hello1&btnG=Google+Search&aq=f&oq= HTTP/1.1\r\n"
			"Host: www.google.com\r\n"
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9\r\n"
			"Accept-Language: en-us,en;q=0.5\r\n"
			"Accept-Encoding: gzip,deflate\r\n"
			"Accept-Charset: x-gbk,utf-8;q=0.7,*;q=0.7\r\n"
			"Keep-Alive: 300\r\n"
			"Connection: keep-alive\r\n";
	HTTPRequestPacket packet;
	packet.parsePacket(require, strlen(require));

	CPPUNIT_ASSERT(false ==  checkSeachRule(packet));
	}

	{
	char * require = "GET /search?hl=en&q=hhhhhhhhhhhhhhhhhhhhhhhhhh&btnG=Google+Search&aq=f&oq= HTTP/1.1\r\n"
			"Host: www.google.com\r\n"
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9\r\n"
			"Accept-Language: en-us,en;q=0.5\r\n"
			"Accept-Encoding: gzip,deflate\r\n"
			"Accept-Charset: x-gbk,utf-8;q=0.7,*;q=0.7\r\n"
			"Keep-Alive: 300\r\n"
			"Connection: keep-alive\r\n";
	HTTPRequestPacket packet;
	packet.parsePacket(require, strlen(require));

	CPPUNIT_ASSERT(true ==  checkSeachRule(packet));
	}
}
