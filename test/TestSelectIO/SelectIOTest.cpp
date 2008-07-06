#include "StdAfx.h"
#include ".\selectiotest.h"
#include <map>
using namespace std;

SelectIOTest::SelectIOTest(void) {
}

SelectIOTest::~SelectIOTest(void) {
}

namespace {

// 用于保存于SOCKET对应的数据
typedef map<SOCKET, char *> SOCK_DATA;
SOCK_DATA g_SockData;

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
	return 0;
}
} // return 0;


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

void SelectIOTest::testPostSelect() {
char *data1 = "HTTP/1.1 200 OK\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 5\r\n"
"Content-Type: text/html\r\n"
"Connection: close\r\n\r\n"
"12345";

char *data2 = "HTTP/1.1 200 OK\r\n"
"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
"Accept-Ranges: bytes\r\n"
"Content-Length: 5\r\n"
"Content-Type: image/jpeg\r\n"
"Connection: close\r\n\r\n"
"12345";
//初始化数据
	g_SockData.clear();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));
	g_SockData.insert(make_pair(s, data2));

	// 初始化SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	select.postselect(&readfds);

	// 验证数据
}
