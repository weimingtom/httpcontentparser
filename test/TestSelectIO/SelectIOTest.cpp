#include "StdAfx.h"
#include ".\selectiotest.h"
#include <map>
#include <string>
using namespace std;

SelectIOTest::SelectIOTest(void) {
}

SelectIOTest::~SelectIOTest(void) {
}

namespace {

// 用于保存于SOCKET对应的数据
typedef multimap<SOCKET, string> SOCK_DATA;
SOCK_DATA g_SockData;
int g_bufBegin = 0;

void resetFakeBuffer() {
	g_bufBegin= 0;
	g_SockData.clear();
}

// 一次只读一个包
int WSPAPI WSPRecv(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesRecvd,
	LPDWORD			lpFlags,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
	)
{
	SOCK_DATA::iterator iter = g_SockData.lower_bound(s);
	SOCK_DATA::const_iterator iterEnd = g_SockData.upper_bound(s);
	
	int moveSize = 0;
	for (; iter != iterEnd; ++iter) {
		const int bytes = iter->second.length();
		if (moveSize + bytes <= g_bufBegin) {
			moveSize += bytes;
			continue;
		}

		const int bytes_written = WriteToBuffer(lpBuffers, dwBufferCount, 0, 
			iter->second.c_str(), iter->second.length());
		*lpNumberOfBytesRecvd = bytes_written;
		break;
	}

	*lpErrno = 0;

	// 则不影响指针
	if (0 == ((*lpFlags) & MSG_PEEK)) {
		g_bufBegin += *lpNumberOfBytesRecvd;
	}
	
	return 0;
}
} // namespace


// 测试混合内容
// 让一个完整的包，后面跟着一个88
void SelectIOTest::testMax() {
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 45\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	string data = "88";
}

void SelectIOTest::testConstantPackets() {
}
void SelectIOTest::testZeroChunk() {
	// 测试没有长度的chunk
	string data1 = "HTTP/1.1 302 Found\r\n"
	"Date: Thu, 10 Jul 2008 15:46:27 GMT\r\n"
	"Server: Apache/1.3.29 (Unix) PHP/4.3.4\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n"
	"Transfer-Encoding: chunked\r\n\r\n"
	"0\r\n\r\n";

	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;

	// 初始化SelectIO
	resetFakeBuffer();
	const SOCKET s = 10831;
	CSelectIO select;
	resetFakeBuffer();
	select.setRecv(WSPRecv);
	g_SockData.insert(make_pair(s, data1));

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT( 0 == select.preselect(&readfds));
}
void SelectIOTest::testMulitPacket() {
		// test case 1: 简单验证
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 45\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	string data2 = "1234567890123456789012345678901234567890";

	//初始化数据
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// 验证数据
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;

	// 初始化SelectIO
	CSelectIO select;
	resetFakeBuffer();
	select.setRecv(WSPRecv);

	g_SockData.insert(make_pair(s, data1));
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 1);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == 0);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 1);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == 0);

	g_SockData.insert(make_pair(s, data2));
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	FD_SET(s, &readfds);
	select.postselect(&readfds);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == data2.length() + data1.length());
	}
}

void SelectIOTest::testCopyBuffer() {
	char buffer1[2];
	char buffer2[3];
	char buffer3[4];
	WSABUF wsabuf[3];
	wsabuf[0].buf = buffer1;
	wsabuf[0].len = 2;
	wsabuf[1].buf = buffer2;
	wsabuf[1].len = 3;
	wsabuf[2].buf = buffer3;
	wsabuf[2].len = 4;

	const char data1[] = "388888888888888888888888888888888888888888888888888";
	CPPUNIT_ASSERT(getBufferTotalSize(wsabuf, 3) == 9);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 0, data1, strlen(data1)) == 
		getBufferTotalSize(wsabuf, 3));
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3), data1, strlen(data1)) == 0);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)+1, data1, strlen(data1)) == 0);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)-1, data1, strlen(data1)) == 1);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)-2, data1, strlen(data1)) == 2);
}

// 传入一个非法的HTTP包，查看反应
void SelectIOTest::testInvalidateHTTPPacket() {
		{
	string data1 = "HMTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	//初始化数据
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// 初始化SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	}
}

void SelectIOTest::testPostSelect() {
	// test case 1: 简单验证
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	//初始化数据
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// 初始化SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	// 验证数据
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length()));
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 1);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == 0);
	}

	// 一次传入三个包
	// 并分别读取他们
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	string data2 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"23456";

	string data3 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"34567";

		//初始化数据
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));
	g_SockData.insert(make_pair(s, data2));
	g_SockData.insert(make_pair(s, data3));


	// 初始化SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	
	// 验证数据
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;

	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length()));

	// 在包没有完成时，应该直接返回1
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data2.length()));

	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data3.length()));
	}
}


void SelectIOTest::testPreSelect() {
	CSelectIO select;
	select.setRecv(WSPRecv);

	fd_set readfds;
	FD_ZERO(&readfds);
	CPPUNIT_ASSERT(1 == select.preselect(&readfds));
	CPPUNIT_ASSERT(1 == select.preselect(NULL));

	FD_SET(111, &readfds);
	FD_SET(1111, &readfds);
	CPPUNIT_ASSERT(1 == select.preselect(&readfds));
}
