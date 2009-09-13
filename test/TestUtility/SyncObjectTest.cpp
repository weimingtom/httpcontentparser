#include "StdAfx.h"
#include ".\syncobjecttest.h"
#include <utility\syncutility.h>
#include <utility\protocolpacket.h>

using namespace yanglei_utility;



::CRITICAL_SECTION cs_;

const char *p1 = "1 CASE TEST";
const char *p2 = "2 CASE TEST";
const char *p3 = "3 CASE TEST";
const char *p4 = "4 CASE TEST";

DWORD CALLBACK OrigCriticalSection(LPVOID pParam) {
	EnterCriticalSection(&cs_);

	char * p = (char*)pParam;
	printf("\n");
	printf("OrigCriticalSection %s 1\n", p);
	printf("OrigCriticalSection %s 2\n", p);
	printf("OrigCriticalSection %s 3\n", p);
	printf("OrigCriticalSection %s 4\n", p);

	LeaveCriticalSection(&cs_);

	return 0;
}

void testCase1() {
	DWORD dwThread;
	
	::InitializeCriticalSection(&cs_);
	CreateThread(NULL, 1, OrigCriticalSection, (LPVOID)p1, 0, &dwThread);
	CreateThread(NULL, 1, OrigCriticalSection, (LPVOID)p2, 0, &dwThread);
	CreateThread(NULL, 1, OrigCriticalSection, (LPVOID)p3, 0, &dwThread);
	CreateThread(NULL, 1, OrigCriticalSection, (LPVOID)p4, 0, &dwThread);
	// ::DeleteCriticalSection(&cs_);
	Sleep(500);
}


CAutoCreateCS auto_lock;
DWORD CALLBACK AutoCriticalSectionProc(LPVOID pParam) {
	yanglei_utility::SingleLock<CAutoCreateCS> lock(&auto_lock);

	char * p = (char*)pParam;
	printf("\n");
	printf("AutoCriticalSectionProc %s 1\n", p);
	printf("AutoCriticalSectionProc %s 2\n", p);
	printf("AutoCriticalSectionProc %s 3\n", p);
	printf("AutoCriticalSectionProc %s 4\n", p);

	return 0;
}


void testAutoCriticalSection() {
	DWORD dwThread;
	CreateThread(NULL, 1, AutoCriticalSectionProc, (LPVOID)p1, 0, &dwThread);
	CreateThread(NULL, 1, AutoCriticalSectionProc, (LPVOID)p2, 0, &dwThread);
	CreateThread(NULL, 1, AutoCriticalSectionProc, (LPVOID)p3, 0, &dwThread);
	CreateThread(NULL, 1, AutoCriticalSectionProc, (LPVOID)p4, 0, &dwThread);
	Sleep(500);
}

//=============================================
// test sysmutex

DWORD CALLBACK TheadTestMutexNamed(LPVOID pParam) {
	CSysMutex g_unamed_mutex("24483F0A-A8B1-4a37-8E47-26E256C10884");
	SingleLock<CSysMutex> lock(&g_unamed_mutex);
	char * p = (char*)pParam;
	printf("\n");;
	printf("testSysMutexWithName %s 1\n", p);
	printf("testSysMutexWithName %s 2\n", p);
	printf("testSysMutexWithName %s 3\n", p);
	printf("testSysMutexWithName %s 4\n", p);

	return 0;
}

void testSysMutexWithName() {

	DWORD dwThread;
	CreateThread(NULL, 1, TheadTestMutexNamed, (LPVOID)p1, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexNamed, (LPVOID)p2, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexNamed, (LPVOID)p3, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexNamed, (LPVOID)p4, 0, &dwThread);
	Sleep(500);
}


CSysMutex g_unamed_mutex;
DWORD CALLBACK TheadTestMutexUnnamed(LPVOID pParam) {
	SingleLock<CSysMutex> lock(&g_unamed_mutex);

	char * p = (char*)pParam;
	printf("\n");
	printf("TheadTestMutexUnnamed %s 1\n", p);
	printf("TheadTestMutexUnnamed %s 2\n", p);
	printf("TheadTestMutexUnnamed %s 3\n", p);
	printf("TheadTestMutexUnnamed %s 4\n", p);

	return 0;
}

void testSysMutexWithoutName() {
	DWORD dwThread;
	CreateThread(NULL, 1, TheadTestMutexUnnamed, (LPVOID)p1, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexUnnamed, (LPVOID)p2, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexUnnamed, (LPVOID)p3, 0, &dwThread);
	CreateThread(NULL, 1, TheadTestMutexUnnamed, (LPVOID)p4, 0, &dwThread);
	Sleep(500);
}