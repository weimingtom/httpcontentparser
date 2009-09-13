#include "StdAfx.h"
#include ".\protocolpackettest.h"
#include <utility\protocolpacket.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

#define BUF_SIZE = (1024 * 16);



void  testGetBytesCanRead() {
	const unsigned buf_size = 100;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buf_read[1024] = {0};
	packet->write(buf_read, 1024);

	BOOST_ASSERT(10 == packet->read(buf_read, 10));
	BOOST_ASSERT(1014 == packet->getBytesCanRead());
	BOOST_ASSERT(10 == packet->read(buf_read, 10));
	BOOST_ASSERT(1004 == packet->getBytesCanRead());
	BOOST_ASSERT(1000 == packet->read(buf_read, 1000));
	BOOST_ASSERT(4 == packet->getBytesCanRead());
	BOOST_ASSERT(4 == packet->read(buf_read, 4));
	BOOST_ASSERT(0 == packet->getBytesCanRead());
	delete packet;
}
void testSeekRead() {
	{
		// 这里如果 buf = 1会失败，不过也没有什么好办法吧
		const unsigned buf_size = 2;
		char buf_read[12] = {0};
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

		BOOST_ASSERT(0 == packet->read(buf_read, 11));
		char buffer[] = "hello world";
		unsigned len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		
		memset(buf_read, 0, sizeof(buf_read));
		packet->seek_read(0);
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 10);
		BOOST_ASSERT(std::string(buf_read) == std::string("lo worldhe"));

		packet->seek_read(11);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 8);
		BOOST_ASSERT(std::string(buf_read) == std::string("hello wo"));
		delete packet;
	}

	{
		const unsigned buf_size = 18;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "hello world";
		unsigned len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf_read[12] = {0};
		packet->seek_read(0);
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string("lo worldhel"));

		packet->seek_read(11);
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));
		delete packet;
	}

	{
		const unsigned buf_size = 11;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "hello world";
		int len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf_read[12] = {0};
		packet->seek_read(0);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string("lo worldhel"));

		packet->seek_read(11);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));
		delete packet;
	}

	{
		const unsigned buf_size = 2;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "hello world";
		int len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf_read[12] = {0};
		packet->seek_read(0);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 9);
		BOOST_ASSERT(std::string(buf_read) == std::string("lo worldh"));

		packet->seek_read(4);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 8);
		BOOST_ASSERT(std::string(buf_read) == std::string("o worldh"));

		packet->seek_read(33);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		BOOST_ASSERT(std::string(buf_read) == std::string(buffer));
		delete packet;

	}

	{
		// 缓存区比要读的空间小
		const unsigned buf_size = 2;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "hello world";
		int len = (int)strlen(buffer);
		int loop_cnt = 1;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf_read[1024] = {0};
		packet->seek_read(4);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 1024);
		BOOST_ASSERT(std::string(buf_read) == std::string("o world"));
	}
}


void testSeekWrite() {
	const unsigned buf_size = 11;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}
	BOOST_ASSERT(packet->getTotalSize() == len * loop_cnt);
	packet->seek_write(0);
	packet->write(_strupr(buffer), len);
	delete packet;
}
void testWrite() {
	const unsigned buf_size = 5;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}
	BOOST_ASSERT(packet->getTotalSize() == len * loop_cnt);
	delete packet;

	{
		const unsigned buf_size = 12;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

		char buffer[] = "hello world";
		int len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}
		BOOST_ASSERT(packet->getTotalSize() == len * loop_cnt);
		delete packet;
	}

	{
		const unsigned buf_size = 83;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

		char buffer[] = "hello world";
		int len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}
		BOOST_ASSERT(packet->getTotalSize() == len * loop_cnt);
		delete packet;
	}

	// 写入场子付出昂
	{
		char buffer[1024];
		for(int i= 0; i<1024;i++) {
			buffer[i] = 'a';
		}
		const unsigned buf_size = 83;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		packet->write(buffer, 1024);
		BOOST_ASSERT(packet->getTotalSize() == 1024);
		delete packet;
	}
}

void testLoopRead() {
	// 只读取一个字符
	{
		const unsigned buf_size = 3;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "abc";
		int len = (int)strlen(buffer);
		int loop_cnt = 1 ;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf[12] = {0};
		int dwRead = packet->read(buf, 1);
		BOOST_ASSERT(buf[0] == 'a');
		BOOST_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		BOOST_ASSERT(buf[0] == 'b');
		BOOST_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		BOOST_ASSERT(buf[0] == 'c');
		BOOST_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		BOOST_ASSERT(dwRead == 0);


		delete packet;
	}

	{
		const unsigned buf_size = 3;
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
		char buffer[] = "abcdefghijklmnopqrstuvwxyz";
		int len = (int)strlen(buffer);
		int loop_cnt = 1 ;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		char buf[12] = {0};
		int dwRead = packet->read(buf, 1);
		int index = 'a';
		while (dwRead != 0) {
			BOOST_ASSERT(buf[0] == index);
			dwRead = packet->read(buf, 1);
			if (index == 'z')
				index = 'a';
			else
				index ++;
		}

		delete packet;
	}
}

// testRead一些列函数测试不同默认缓冲区下
// 的读写操作
void testRead() {
	{
	const unsigned buf_size = 10;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}

	char buf_read[34], buf_gen[34];
	memset(buf_read, 0, sizeof(buf_read));
	packet->read(buf_read, 33);
	buf_read[33]  = '\0';
	len = (int)strlen(buffer);
	for (int i = 0; i < 3; ++i) {
		strcpy(&(buf_gen[len*i]), buffer); 
	}
	BOOST_ASSERT(std::string(buf_read) == std::string(buf_gen));
	delete packet;
	}
	{
	const unsigned buf_size = 1024;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}

	char buf_read[34], buf_gen[34];
	memset(buf_read, 0, sizeof(buf_read));
	packet->read(buf_read, 33);
	buf_read[33]  = '\0';
	len = (int)strlen(buffer);
	for (int i = 0; i < 3; ++i) {
		strcpy(&(buf_gen[len*i]), buffer); 
	}
	BOOST_ASSERT(std::string(buf_read) == std::string(buf_gen));
	delete packet;
	}
	{
	const unsigned buf_size = 1;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}

	char buf_read[34], buf_gen[34];
	memset(buf_read, 0, sizeof(buf_read));
	packet->read(buf_read, 33);
	buf_read[33]  = '\0';
	len = (int)strlen(buffer);
	for (int i = 0; i < 3; ++i) {
		strcpy(&(buf_gen[len*i]), buffer); 
	}
	BOOST_ASSERT(std::string(buf_read) == std::string(buf_gen));
	delete packet;
	}
	{
	const unsigned buf_size = 11;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}

	char buf_read[34], buf_gen[34];
	memset(buf_read, 0, sizeof(buf_read));
	packet->read(buf_read, 33);
	buf_read[33]  = '\0';
	len = (int)strlen(buffer);
	for (int i = 0; i < 3; ++i) {
		strcpy(&(buf_gen[len*i]), buffer); 
	}
	BOOST_ASSERT(std::string(buf_read) == std::string(buf_gen));
	delete packet;
	}
}