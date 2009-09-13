#include "StdAfx.h"
#include ".\replacepackettest.h"
#include <utility\replacepacket.h>
#include <utility\HttpPacket.h>

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


void testNewPacket() {
	int written;
	HTTPPacket *packet = new HTTPPacket;
	packet->addBuffer(packet1, static_cast<int>(strlen(packet1)), &written);
	HTTPPacket *new_packet = new HTTPPacket;

	FillBlankPacket(packet, new_packet);

    BOOST_ASSERT(0 == strcmp(new_packet->getHeader()->getDate(), "Thu, 24 Apr 2008 02:37:48 GMT"));
	BOOST_ASSERT(0 == strcmp(new_packet->getHeader()->getHeaderLine(), "HTTP/1.1 302 Found"));
	BOOST_ASSERT(0 == strcmp(new_packet->getHeader()->getServer(), "Apache/1.3.37 (Unix) mod_gzip/1.3.26.1"));
	BOOST_ASSERT(new_packet->isComplete());
	int a = new_packet->getDataSize() ;
	BOOST_ASSERT(new_packet->getDataSize() == 723);
	delete packet;
    delete new_packet;
}