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
	int total_size = g_bufBegin;
	for (; iter != iterEnd; ++iter) {
		const int bytes = iter->second.length();
		const int bytes_written = WriteToBuffer(lpBuffers, dwBufferCount, total_size, 
			iter->second.c_str(), iter->second.length());
		
		total_size += bytes_written;
		assert(bytes_written <= bytes);
	}

	*lpNumberOfBytesRecvd = total_size - g_bufBegin;
	*lpErrno = 0;

	// 则不影响指针
	if (0 == ((*lpFlags) & MSG_PEEK)) {
		g_bufBegin += total_size;
	}
	
	return 0;
}
} // namespace

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
	select.checkSetting_.setCheckHTML(true);
	select.checkSetting_.setCheckImage(true);
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
	select.checkSetting_.setCheckHTML(true);
	select.checkSetting_.setCheckImage(true);
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
	"12345";

	string data3 = "HTTP/1.1 200 OK\r\n"
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
	g_SockData.insert(make_pair(s, data2));
	g_SockData.insert(make_pair(s, data3));


	// 初始化SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	select.checkSetting_.setCheckHTML(true);
	select.checkSetting_.setCheckImage(true);
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

	// 对与两个完整的包，且在一个TCP包当中可以一下写入到缓冲区当中吧
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length() + data2.length() + data3.length()));
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
