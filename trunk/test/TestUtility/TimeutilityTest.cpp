#include "StdAfx.h"
#include ".\timeutilitytest.h"
#include <time.h>
#include <io.h>
#include <stdlib.h>
#include <utility/strutility.h>

using namespace strutility;
using namespace timeutility;

//===========================================
// constructor and deconstructor
TimeutilityTest::TimeutilityTest(void) {
}

TimeutilityTest::~TimeutilityTest(void) {
}


//===========================================
// 
void TimeutilityTest::testMintueTimespan() {
}


void TimeutilityTest::testUSFormatTime() {
	TCHAR buffer[1024];
	SYSTEMTIME tm;

	// test case1
	TCHAR *expect1= "08:12 am 02/26/2008";
	tm.wDay = 26;
	tm.wHour = 8;
	tm.wMonth = 2;
	tm.wYear = 2008;
	tm.wMinute = 12;
	USFormatTime(tm, buffer, 1024);
	CPPUNIT_ASSERT(0 == _tcscmp(buffer, expect1));

	// test case2
	TCHAR *expect2 = "12:12 am 02/26/2008";
	tm.wDay = 26;
	tm.wHour = 12;
	tm.wMonth = 2;
	tm.wYear = 2008;
	tm.wMinute = 12;
	USFormatTime(tm, buffer, 1024);
	CPPUNIT_ASSERT(0 == _tcscmp(buffer, expect2));

	// test case3
	TCHAR *expect3 = "08:12 pm 02/26/2008";
	tm.wDay = 26;
	tm.wHour = 20;
	tm.wMonth = 2;
	tm.wYear = 2008;
	tm.wMinute = 12;
	USFormatTime(tm, buffer, 1024);
	CPPUNIT_ASSERT(0 == _tcscmp(buffer, expect3));
}

void TimeutilityTest::testTmfromString() {
	{
	struct tm t = tmfromstring(TEXT("1999-12-1 12:12:00"));
	CPPUNIT_ASSERT(t.tm_year == 1999);
	CPPUNIT_ASSERT(t.tm_mon == 12);
	CPPUNIT_ASSERT(t.tm_mday == 1);
	CPPUNIT_ASSERT(t.tm_hour == 12);
	CPPUNIT_ASSERT(t.tm_min == 12);
	CPPUNIT_ASSERT(t.tm_sec == 0);
	}

	{
	struct tm t = tmfromstring(TEXT("1999/12/09 12:12:34"));
	CPPUNIT_ASSERT(t.tm_year == 1999);
	CPPUNIT_ASSERT(t.tm_mon == 12);
	CPPUNIT_ASSERT(t.tm_mday == 9);
	CPPUNIT_ASSERT(t.tm_hour == 12);
	CPPUNIT_ASSERT(t.tm_min == 12);
	CPPUNIT_ASSERT(t.tm_sec == 34);
	}

	{
	struct tm t = tmfromstring(TEXT("1999/12/09"));
	CPPUNIT_ASSERT(t.tm_year == 1999);
	CPPUNIT_ASSERT(t.tm_mon == 12);
	CPPUNIT_ASSERT(t.tm_mday == 9);
	CPPUNIT_ASSERT(t.tm_hour == 0);
	CPPUNIT_ASSERT(t.tm_min == 0);
	CPPUNIT_ASSERT(t.tm_sec == 0);
	}

	{
	struct tm t = tmfromstring(TEXT("1999-12-09"));
	CPPUNIT_ASSERT(t.tm_year == 1999);
	CPPUNIT_ASSERT(t.tm_mon == 12);
	CPPUNIT_ASSERT(t.tm_mday == 9);
	CPPUNIT_ASSERT(t.tm_hour == 0);
	CPPUNIT_ASSERT(t.tm_min == 0);
	CPPUNIT_ASSERT(t.tm_sec == 0);
	}
}