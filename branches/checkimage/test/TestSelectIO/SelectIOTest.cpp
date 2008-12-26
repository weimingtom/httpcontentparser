#include "StdAfx.h"
#include ".\selectiotest.h"
#include <map>
#include <set>
#include <string>
using namespace std;

SelectIOTest::SelectIOTest(void) {
}

SelectIOTest::~SelectIOTest(void) {
}

namespace {

// ���ڱ�����SOCKET��Ӧ������
typedef multimap<SOCKET, string> SOCK_DATA;
SOCK_DATA g_SockData;
int g_bufBegin = 0;

void resetFakeBuffer() {
	g_bufBegin= 0;
	g_SockData.clear();
}

int WSPAPI myCloseSocket(
	SOCKET		s,
	LPINT	lpErrno) {
	return 0;
}
// һ��ֻ��һ����
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
		const int bytes = static_cast<const int>(iter->second.length());
		if (moveSize + bytes <= g_bufBegin) {
			moveSize += bytes;
			continue;
		}

		const int bytes_written = WriteToBuffer(lpBuffers, dwBufferCount, 0, 
			iter->second.c_str(), static_cast<const int>(iter->second.length()));
		*lpNumberOfBytesRecvd = bytes_written;
		break;
	}

	*lpErrno = 0;

	// ��Ӱ��ָ��
	if (0 == ((*lpFlags) & MSG_PEEK)) {
		g_bufBegin += *lpNumberOfBytesRecvd;
	}
	
	return 0;
}
} // namespace


void SelectIOTest::testCloseSocket() {
	string data1 = "HTTP/1.1 200 OK\r\n"
		"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
		"Accept-Ranges: bytes\r\n"
		"Content-Length: 5\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n\r\n"
		"12345";

	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));


	// ��ʼ��SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	//select.setCloseSocket(myCloseSocket);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	
	// ��֤����
	//const int buf_size = 1024 * 64;
	//char buffer[buf_size];
	//WSABUF wsabuf;
	//wsabuf.buf = buffer;
	//wsabuf.len = buf_size;
	//DWORD dwNumberOfBytesRecvd;

	//FD_ZERO(&readfds);
	//FD_SET(s, &readfds);
	//CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	//select.postselect(&readfds);

	//FD_ZERO(&readfds);
	//FD_SET(s, &readfds);
	//CPPUNIT_ASSERT( 1 == select.preselect(&readfds));

	//// ����closeSockets)
	//select.onCloseSocket(s);
	//FD_ZERO(&readfds); 
	//FD_SET(s, &readfds);
	//CPPUNIT_ASSERT( 0 == select.preselect(&readfds));
	//CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
	//	1, &dwNumberOfBytesRecvd) == 0);
	//CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length()));
}

// ���Ի������
// ��һ�������İ����������һ��88
void SelectIOTest::testMax() {
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"12345";

	string data2 = "88";

	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));


	// ��ʼ��SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	
	// ��֤����
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;

	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT( 0 == select.preselect(&readfds));
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 0);
	CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length()));

	g_SockData.insert(make_pair(s, data2));
	// �ڶ����ݵ�ʱ�� ���ݲ��ᱻ��ȡ
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	CPPUNIT_ASSERT(1 == readfds.fd_count);
	CPPUNIT_ASSERT(select.prerecv(s, &wsabuf,
		1, &dwNumberOfBytesRecvd) == 1);
}


void SelectIOTest::testZeroChunk() {
	// ����û�г��ȵ�chunk
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

	// ��ʼ��SelectIO
	resetFakeBuffer();
	const SOCKET s = 10831;
	CSelectIO select;
	resetFakeBuffer();
	select.setRecv(WSPRecv);
	g_SockData.insert(make_pair(s, data1));
}
void SelectIOTest::testMulitPacket() {
		// test case 1: ����֤
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 45\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"12345";

	string data2 = "1234567890123456789012345678901234567890";

	//��ʼ������
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// ��֤����
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;

	// ��ʼ��SelectIO
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
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 0, data1, static_cast<const int>(strlen(data1))) == 
		getBufferTotalSize(wsabuf, 3));
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3), data1, static_cast<const int>(strlen(data1))) == 0);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)+1, data1, static_cast<const int>(strlen(data1))) == 0);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)-1, data1, static_cast<const int>(strlen(data1))) == 1);
	CPPUNIT_ASSERT(WriteToBuffer(wsabuf, 3, 
		getBufferTotalSize(wsabuf, 3)-2, data1, static_cast<const int>(strlen(data1))) == 2);
}

// ����һ���Ƿ���HTTP�����鿴��Ӧ
void SelectIOTest::testInvalidateHTTPPacket() {
		{
	string data1 = "HMTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n\r\n"
	"12345";

	//��ʼ������
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// ��ʼ��SelectIO
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
	// test case 1: ����֤
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"12345";

	//��ʼ������
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));

	// ��ʼ��SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
	select.postselect(&readfds);
	// ��֤����
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

	// һ�δ���������
	// ���ֱ��ȡ����
	{
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"12345";

	string data2 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"23456";

	string data3 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"34567";

	//��ʼ������
	resetFakeBuffer();
	const SOCKET s = 10831;
	g_SockData.insert(make_pair(s, data1));
	g_SockData.insert(make_pair(s, data2));
	g_SockData.insert(make_pair(s, data3));


	// ��ʼ��SelectIO
	CSelectIO select;
	select.setRecv(WSPRecv);
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(s, &readfds);
	
	// ��֤����
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

	// �ڰ�û�����ʱ��Ӧ��ֱ�ӷ���1
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

void SelectIOTest::testConstantPackets() {
	// ���ݻ�����
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	// fd_set readfds;
}

void SelectIOTest::testRemovePacket() {
	// testcase
	// ����������socket �������� Ȼ��ֱ�ȥ��
	// ��������Packet���Ƿ���Ȼ����δ��ɵİ�
	string data1 = "HTTP/1.1 200 OK\r\n"
	"Date: Thu, 24 Apr 2008 02:37:48 GMT\r\n"
	"Accept-Ranges: bytes\r\n"
	"Content-Length: 5\r\n"
	"Content-Type: text/html\r\n"
	"Connection: keep-alive\r\n\r\n"
	"12345";

	// ���ݻ�����
	const int buf_size = 1024 * 64;
	char buffer[buf_size];
	WSABUF wsabuf;
	wsabuf.buf = buffer;
	wsabuf.len = buf_size;
	DWORD dwNumberOfBytesRecvd;
	fd_set readfds;

	{
	CSelectIO select;
	select.setRecv(WSPRecv);
	resetFakeBuffer();
	set<SOCKET> socket_set;
	// ����һЩ��socket
	set<SOCKET>::iterator iter = socket_set.begin();
	socket_set.insert(11502);
	socket_set.insert(5130);
	socket_set.insert(1320);
	socket_set.insert(4510);
	socket_set.insert(1023);
	socket_set.insert(104);
	socket_set.insert(120);

	// ��������
	for (; iter != socket_set.end(); ++iter) {
		g_SockData.insert(make_pair(*iter, data1));
	}

	int cnt = static_cast<int>(socket_set.size());
	for (; iter != socket_set.end(); ++iter) {
		CPPUNIT_ASSERT(select.socketPackets_._sockets_map_.size() == cnt);
		FD_ZERO(&readfds);
		FD_SET(*iter, &readfds);

		CPPUNIT_ASSERT( 1 == select.preselect(&readfds));
		select.postselect(&readfds);
		CPPUNIT_ASSERT(select.prerecv(*iter, &wsabuf,
			1, &dwNumberOfBytesRecvd) == 0);
		CPPUNIT_ASSERT(dwNumberOfBytesRecvd == (data1.length()));
		cnt--;
	}
	CPPUNIT_ASSERT(select.socketPackets_._sockets_map_.size() == 0);
	}
}
