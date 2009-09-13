#include "StdAfx.h"
#include ".\timeutilitytest.h"
#include <time.h>
#include <io.h>
#include <stdlib.h>
#include <utility/strutility.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

using namespace strutility;
using namespace timeutility;

//===========================================
// constructor and deconstructor


//===========================================
// 
void testMintueTimespan() {
}


void testUSFormatTime() {
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
	BOOST_ASSERT(0 == _tcscmp(buffer, expect1));

	// test case2
	TCHAR *expect2 = "12:12 am 02/26/2008";
	tm.wDay = 26;
	tm.wHour = 12;
	tm.wMonth = 2;
	tm.wYear = 2008;
	tm.wMinute = 12;
	USFormatTime(tm, buffer, 1024);
	BOOST_ASSERT(0 == _tcscmp(buffer, expect2));

	// test case3
	TCHAR *expect3 = "08:12 pm 02/26/2008";
	tm.wDay = 26;
	tm.wHour = 20;
	tm.wMonth = 2;
	tm.wYear = 2008;
	tm.wMinute = 12;
	USFormatTime(tm, buffer, 1024);
	BOOST_ASSERT(0 == _tcscmp(buffer, expect3));
}

void testTmfromString() {
	{
	struct tm t = tmfromstring(TEXT("1999-12-1 12:12:00"));
	BOOST_ASSERT(t.tm_year == 1999);
	BOOST_ASSERT(t.tm_mon == 12);
	BOOST_ASSERT(t.tm_mday == 1);
	BOOST_ASSERT(t.tm_hour == 12);
	BOOST_ASSERT(t.tm_min == 12);
	BOOST_ASSERT(t.tm_sec == 0);
	}

	{
	struct tm t = tmfromstring(TEXT("1999/12/09 12:12:34"));
	BOOST_ASSERT(t.tm_year == 1999);
	BOOST_ASSERT(t.tm_mon == 12);
	BOOST_ASSERT(t.tm_mday == 9);
	BOOST_ASSERT(t.tm_hour == 12);
	BOOST_ASSERT(t.tm_min == 12);
	BOOST_ASSERT(t.tm_sec == 34);
	}

	{
	struct tm t = tmfromstring(TEXT("1999/12/09"));
	BOOST_ASSERT(t.tm_year == 1999);
	BOOST_ASSERT(t.tm_mon == 12);
	BOOST_ASSERT(t.tm_mday == 9);
	BOOST_ASSERT(t.tm_hour == 0);
	BOOST_ASSERT(t.tm_min == 0);
	BOOST_ASSERT(t.tm_sec == 0);
	}

	{
	struct tm t = tmfromstring(TEXT("1999-12-09"));
	BOOST_ASSERT(t.tm_year == 1999);
	BOOST_ASSERT(t.tm_mon == 12);
	BOOST_ASSERT(t.tm_mday == 9);
	BOOST_ASSERT(t.tm_hour == 0);
	BOOST_ASSERT(t.tm_min == 0);
	BOOST_ASSERT(t.tm_sec == 0);
	}
}