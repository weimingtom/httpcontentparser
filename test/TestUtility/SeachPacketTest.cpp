#include "StdAfx.h"
#include ".\seachpackettest.h"
#include <utility\SeachPacket.h>
#include <utility\httprequestPacket.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


// 对于主流的搜索引擎其hostname, 全部都是 search.**.com
// 如search.yahoo.com
void yahooTest() {
	//GET http://www.yahoo.com/r/sx/*-http://search.yahoo.com/search?p=word&vc=&fr=yfp-t-501&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1
	//Referer: http://www.yahoo.com/
	//Accept-Encoding: gzip,deflate,bzip2,sdch
	//Accept-Language: zh-CN,zh
	//Accept-Charset: gb18030,*,utf-8
	//Host: www.yahoo.com
	//Proxy-Connection: Keep-Alive
	{
		char * oper = "http://www.yahoo.com/r/sx/*-http://search.yahoo.com/search?p=word&vc=&fr=yfp-t-501&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1";
		char * host_name = "search.yahoo.com";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("word", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}


	// test case 2
	//GET http://search.yahoo.com/search?p=word&vc=&fr=yfp-t-501&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1
	//Referer: http://www.yahoo.com/
	//Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
	//Accept-Encoding: gzip,deflate,bzip2,sdch
	//Accept-Language: zh-CN,zh
	//Accept-Charset: gb18030,*,utf-8
	//Host: search.yahoo.com
	//Proxy-Connection: Keep-Alive
	{
		char * oper = "http://search.yahoo.com/search?p=word&vc=&fr=yfp-t-501&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1";
		char * host_name = "search.yahoo.com";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("word", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}
}

void googleTest() {
	//GET http://www.google.com/search?hl=en&q=word&btnG=Google+Search&aq=f&oq=wor HTTP/1.1
	//Referer: http://www.google.com/
	//Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
	//Accept-Encoding: gzip,deflate,bzip2,sdch
	//Accept-Language: zh-CN,zh
	//Accept-Charset: gb18030,*,utf-8
	//Host: www.google.com
	//Proxy-Connection: Keep-Alive

	{
	char * oper = "http://www.google.com/search?hl=en&q=word&btnG=Google+Search&aq=f&oq=wor HTTP/1.1";
	char * host_name = "www.google.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	BOOST_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT( 0 == strcmp("word", result));
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}

	//GET /search?hl=zh-CN&newwindow=1&q=aaaaa++bbbbb&btnG=Google+%E6%90%9C%E7%B4%A2&meta= HTTP/1.1
	//Accept-Encoding: gzip,deflate,bzip2,sdch
	//Accept-Language: zh,en-US,en
	//Accept-Charset: ISO-8859-1,*,utf-8
	//Host: www.google.com
	//Connection: Keep-Alive
	{
	char * oper = "GET /search?hl=zh-CN&newwindow=1&q=aaaaa++bbbbb&btnG=Google+%E6%90%9C%E7%B4%A2&meta= HTTP/1.1";
	char * host_name = "www.google.cn";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	BOOST_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT( 0 == strcmp("aaaaa++bbbbb", result));
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}
}
void baiduTest() {
	//GET http://www.baidu.com/s?wd=word HTTP/1.1
	//Referer: http://www.baidu.com/
	//Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5
	//Accept-Encoding: gzip,deflate,bzip2,sdch
	//Accept-Language: zh-CN,zh
	//Accept-Charset: gb18030,*,utf-8
	//Host: www.baidu.com
	//Proxy-Connection: Keep-Alive

	char * oper = "http://www.baidu.com/s?wd=word HTTP/1.1";
	char * host_name = "www.baidu.com";
	char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
	SeachPacket packet;
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
	BOOST_ASSERT( 0 != packet.parse(oper, host_name));
	packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
	BOOST_ASSERT( 0 == strcmp("word", result));
	BOOST_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
}
void getContentTest() {
	{
		char * oper = "/s?wd=ddddddddddddddddddd HTTP/1.1";
		char * host_name = "www.baidu.cn";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("ddddddddddddddddddd", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
	}

	{
		char * oper = "/search?p=ddddddddddddddd&fr=yfp-t-103&toggle=1&cop=mss&ei=UTF-8&fp_ip=CN HTTP/1.1";
		char * host_name = "search.yahoo.com";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("ddddddddddddddd", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}

	{
		char * oper = "/search;_ylt=A0oGki5cNGdK0RAAolyl87UF?p=safdasdf&fr=sfp&fr2=&iscqry= HTTP/1.1";
		char * host_name = "search.yahoo.com";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		int aa = packet.parse(oper, host_name);
		BOOST_ASSERT( 0 != aa);
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("safdasdf", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_YAHOO == packet.getSeachEngineType());
	}


	{
		// 对于google来说， /search才是开头
		// 这也不是一个正常的search
		char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
		char * host_name = "www.google.com";

		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
		BOOST_ASSERT( 0 == packet.parse(oper, host_name));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	}

	{
		// 对于google来说， /search才是开头
		char * oper = "/search?hl=en&q=aaaaaaaaaaaa&btnG=Google+Search&aq=f&oq= HTTP/1.1";
		char * host_name = "www.google.com";

		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}

	{
		// 对于google来说， /search才是开头
		char * oper = "/search?hl=en&q=aaaaaaaaaaaa&btnG=Google+Search&aq=f&oq= HTTP/1.1";
		char * host_name = "www.baidu.com";

		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
		BOOST_ASSERT( 0 == packet.parse(oper, host_name));
	}

	{
		char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
		char * host_name = "www.baidu.com";
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("hhhhhhhhhhhhhhhhhhhhhh", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_BAIDU == packet.getSeachEngineType());
	}

	{
		// 次测试用例的主机地址错误
		char * oper = "/s?ie=gb2312&bs=hhhhhhhhhhhhhhhhhhhhhh&sr=&z=&cl=3&f=8&wd=hhhhhhhhhhhhhhhhhhhhhh&ct=0 HTTP/1.1";
		char * host_name = "c.baidu1.com";
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 == packet.parse(oper, host_name));
	}

	{
		char * oper = "/search?hl=en&q=word&btnG=Search HTTP/1.1";
		char * host_name = "www.google.com//";
		SeachPacket packet;
		char result[HTTP_REQUEST_ITEM_MAX_LENGTH];
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 != packet.parse(oper, host_name));
		packet.get_seach_word(result, HTTP_REQUEST_ITEM_MAX_LENGTH);
		BOOST_ASSERT( 0 == strcmp("word", result));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_GOOGLE == packet.getSeachEngineType());
	}

		{
		// 遇上一个测试用例基本相同，不同者就是search前面没有 "/"
		// 此时的测试是失败的
		char * oper = "search?hl=en&q=word&btnG=Search HTTP/1.1";
		char * host_name = "search.google.com";
		SeachPacket packet;
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN ==packet.getSeachEngineType());
		BOOST_ASSERT( 0 == packet.parse(oper, host_name));
		BOOST_ASSERT(SeachPacket::SEACH_ENGINE_UNKNOWN == packet.getSeachEngineType());
	}
}