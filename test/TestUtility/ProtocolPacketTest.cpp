#include "StdAfx.h"
#include ".\protocolpackettest.h"
#include <utility\protocolpacket.h>
using namespace CPPUNIT_NS;

#define BUF_SIZE = (1024 * 16);

ProtocolPacketTest::ProtocolPacketTest(void) {
}

ProtocolPacketTest::~ProtocolPacketTest(void) {
}



void  ProtocolPacketTest::testGetBytesCanRead() {
	const unsigned buf_size = 100;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();
	char buf_read[1024] = {0};
	packet->write(buf_read, 1024);

	CPPUNIT_ASSERT(10 == packet->read(buf_read, 10));
	CPPUNIT_ASSERT(1014 == packet->getBytesCanRead());
	CPPUNIT_ASSERT(10 == packet->read(buf_read, 10));
	CPPUNIT_ASSERT(1004 == packet->getBytesCanRead());
	CPPUNIT_ASSERT(1000 == packet->read(buf_read, 1000));
	CPPUNIT_ASSERT(4 == packet->getBytesCanRead());
	CPPUNIT_ASSERT(4 == packet->read(buf_read, 4));
	CPPUNIT_ASSERT(0 == packet->getBytesCanRead());
	delete packet;
}
void ProtocolPacketTest::testSeekRead() {
	{
		// 这里如果 buf = 1会失败，不过也没有什么好办法吧
		const unsigned buf_size = 2;
		char buf_read[12] = {0};
		ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

		CPPUNIT_ASSERT(0 == packet->read(buf_read, 11));
		char buffer[] = "hello world";
		unsigned len = (int)strlen(buffer);
		int loop_cnt = 8;
		for(int i = 0; i < loop_cnt; i++) { 
			packet->write(buffer, len);
		}

		
		memset(buf_read, 0, sizeof(buf_read));
		packet->seek_read(0);
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 10);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("lo worldhe"));

		packet->seek_read(11);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 8);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("hello wo"));
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
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("lo worldhel"));

		packet->seek_read(11);
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));
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
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("lo worldhel"));

		packet->seek_read(11);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));
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
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));

		packet->seek_read(3);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 9);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("lo worldh"));

		packet->seek_read(4);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 8);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("o worldh"));

		packet->seek_read(33);
		memset(buf_read, 0, sizeof(buf_read));
		packet->read(buf_read, 11);
		CPPUNIT_ASSERT(std::string(buf_read) == std::string(buffer));
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
		CPPUNIT_ASSERT(std::string(buf_read) == std::string("o world"));
	}
}


void ProtocolPacketTest::testSeekWrite() {
	const unsigned buf_size = 11;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}
	CPPUNIT_ASSERT(packet->getTotalSize() == len * loop_cnt);
	packet->seek_write(0);
	packet->write(_strupr(buffer), len);
	delete packet;
}
void ProtocolPacketTest::testWrite() {
	const unsigned buf_size = 5;
	ProtocolPacket<buf_size> *packet = new ProtocolPacket<buf_size>();

	char buffer[] = "hello world";
	int len = (int)strlen(buffer);
	int loop_cnt = 8;
	for(int i = 0; i < loop_cnt; i++) { 
		packet->write(buffer, len);
	}
	CPPUNIT_ASSERT(packet->getTotalSize() == len * loop_cnt);
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
		CPPUNIT_ASSERT(packet->getTotalSize() == len * loop_cnt);
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
		CPPUNIT_ASSERT(packet->getTotalSize() == len * loop_cnt);
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
		CPPUNIT_ASSERT(packet->getTotalSize() == 1024);
		delete packet;
	}
}

void ProtocolPacketTest::testLoopRead() {
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
		CPPUNIT_ASSERT(buf[0] == 'a');
		CPPUNIT_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		CPPUNIT_ASSERT(buf[0] == 'b');
		CPPUNIT_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		CPPUNIT_ASSERT(buf[0] == 'c');
		CPPUNIT_ASSERT(dwRead == 1);
		dwRead = packet->read(buf, 1);
		CPPUNIT_ASSERT(dwRead == 0);


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
			CPPUNIT_ASSERT(buf[0] == index);
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
void ProtocolPacketTest::testRead() {
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
	CPPUNIT_ASSERT(std::string(buf_read) == std::string(buf_gen));
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
	CPPUNIT_ASSERT(std::string(buf_read) == std::string(buf_gen));
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
	CPPUNIT_ASSERT(std::string(buf_read) == std::string(buf_gen));
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
	CPPUNIT_ASSERT(std::string(buf_read) == std::string(buf_gen));
	delete packet;
	}
}