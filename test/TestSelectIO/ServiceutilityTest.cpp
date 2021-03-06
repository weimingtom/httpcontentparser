#include "StdAfx.h"
#include ".\serviceutilitytest.h"
#include "..\..\projects\PacketsGrasper\serviceUtility.h"
#include <utility/HTTPRequestPacket.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

namespace {
// 用于回复COM服务的状态
class COM_State {
public:
    COM_State() {
    }

    ~COM_State() {
    }
};
};
// 这里的测试与COM的状态有关。
void TestCheckSeachRule() {
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
	packet.parsePacket(require, (int)strlen(require));

	// 注意: 要使此测试成功， 需要在BLACK WORD中添加'hello1'.
	// 否则将会失败
	BOOST_CHECK(false ==  checkSeachRule(&packet));
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
	packet.parsePacket(require, (int)strlen(require));

	BOOST_CHECK(false ==  checkSeachRule(&packet));
	}
}
