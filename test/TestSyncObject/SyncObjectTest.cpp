#include "StdAfx.h"
#include ".\syncobjecttest.h"
#include <utility\protocolpacket.h>

SyncObjectTest::SyncObjectTest(void)
{
}

SyncObjectTest::~SyncObjectTest(void)
{
}

::CRITICAL_SECTION cs_;

DWORD CALLBACK ThreadProc1(LPVOID pParam) {
	//using namespace yanglei_utility;
	//SingleLock<CAutoCreateCS> lock(&cs_);

	EnterCriticalSection(&cs_);

	char * p = (char*)pParam;
	printf("\n");
	printf("%s 1\n", p);
	printf("%s 2\n", p);
	printf("%s 3\n", p);
	printf("%s 4\n", p);

	LeaveCriticalSection(&cs_);

	return 0;
}

yanglei_utility::CAutoCreateCS auto_lock;
DWORD CALLBACK ThreadProc2(LPVOID pParam) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&auto_lock);

	char * p = (char*)pParam;
	printf("\n");
	printf("%s 1\n", p);
	printf("%s 2\n", p);
	printf("%s 3\n", p);
	printf("%s 4\n", p);

	return 0;
}

const char *p1 = "===1 CASE TEST";
const char *p2 = "===2 CASE TEST";
const char *p3 = "1 CASE TEST";
const char *p4 = "2 CASE TEST";
void SyncObjectTest::testCase2() {
	
	DWORD dwThread;
	CreateThread(NULL, 1, ThreadProc2, (LPVOID)p1, 0, &dwThread);
	CreateThread(NULL, 1, ThreadProc2, (LPVOID)p2, 0, &dwThread);

	Sleep(500);
}
void SyncObjectTest::testCase1() {
	DWORD dwThread;
	
	::InitializeCriticalSection(&cs_);
	CreateThread(NULL, 1, ThreadProc1, (LPVOID)p3, 0, &dwThread);
	CreateThread(NULL, 1, ThreadProc1, (LPVOID)p4, 0, &dwThread);
	::DeleteCriticalSection(&cs_);

	Sleep(500);
}