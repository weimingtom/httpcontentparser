#include "StdAfx.h"
#include ".\installdatetest.h"
#include <softwareencrypt\installdate.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <time.h>

InstallDateTest::InstallDateTest(void) {
	rawdate = software_encrypt::getInstallDataTime();
} 

InstallDateTest::~InstallDateTest(void) {
	tm t =	to_tm(rawdate);
	FILETIME ft;
	SYSTEMTIME st = st_from_tm(t);
	SystemTimeToFileTime(&st, &ft);
	software_encrypt::internal_utility::setInstallDateFile(ft);
	software_encrypt::internal_utility::setInstallDataOnRegistry(ft);
	software_encrypt::internal_utility::setInstallDateInWin(ft);
}



void InstallDateTest::TestInstallDateItem() {
	using namespace software_encrypt;
	using namespace boost::posix_time;

	SYSTEMTIME st1 = {0}, st2 = {0}, st3 = {0};
	FILETIME ft1= {0}, ft2  = {0}, ft3 = {0};
 
	{
	memset(&st1, 0, sizeof(SYSTEMTIME));
	st1.wYear = 2009;
	st1.wMonth = 5;
	st1.wDay = 8;
	SystemTimeToFileTime(&st1, &ft1);
	internal_utility::setInstallDateInWin(ft1);

	memset(&st2, 0, sizeof(SYSTEMTIME));
	st2.wYear = 2008;
	st2.wMonth = 5;
	st2.wDay = 8;
	SystemTimeToFileTime(&st2, &ft2);
	internal_utility::setInstallDateFile(ft2);

	memset(&st3, 0, sizeof(SYSTEMTIME));
	st3.wYear = 2006;
	st3.wMonth = 5;
	st3.wDay = 8;
	SystemTimeToFileTime(&st3, &ft3);
	internal_utility::setInstallDataOnRegistry(ft3);

	ptime t1 =getInstallDataTime();
	ptime t2 =from_ftime<ptime>(ft3);
	CPPUNIT_ASSERT(t1 == t2);
	}

	{
	memset(&st1, 0, sizeof(SYSTEMTIME));
	st1.wYear = 2009;
	st1.wMonth = 5;
	st1.wDay = 8;
	SystemTimeToFileTime(&st1, &ft1);
	internal_utility::setInstallDateInWin(ft1);

	memset(&st2, 0, sizeof(SYSTEMTIME));
	st2.wYear = 2006;
	st2.wMonth = 5;
	st2.wDay = 7;
	SystemTimeToFileTime(&st2, &ft2);
	internal_utility::setInstallDateFile(ft2);

	memset(&st3, 0, sizeof(SYSTEMTIME));
	st3.wYear = 2006;
	st3.wMonth = 5;
	st3.wDay = 8;
	SystemTimeToFileTime(&st3, &ft3);
	internal_utility::setInstallDataOnRegistry(ft3);

	ptime t1 =getInstallDataTime();
	ptime t2 =from_ftime<ptime>(ft2);
	std::cout<<"pWin: " << to_simple_string(t1)<< std::endl;
	std::cout<<"pWin: " << to_simple_string(t2)<< std::endl;
	CPPUNIT_ASSERT(t1 == t2);
	}

	{
	memset(&st1, 0, sizeof(SYSTEMTIME));
	st1.wYear = 2007;
	st1.wMonth = 2;
	st1.wDay = 8;
	SystemTimeToFileTime(&st1, &ft1);
	internal_utility::setInstallDateInWin(ft1);

	memset(&st2, 0, sizeof(SYSTEMTIME));
	st2.wYear = 2008;
	st2.wMonth = 5;
	st2.wDay = 8;
	SystemTimeToFileTime(&st2, &ft2);
	internal_utility::setInstallDateFile(ft2);

	memset(&st3, 0, sizeof(SYSTEMTIME));
	st3.wYear = 2007;
	st3.wMonth = 5;
	st3.wDay = 8;
	SystemTimeToFileTime(&st3, &ft3);
	internal_utility::setInstallDataOnRegistry(ft3);

	ptime t1 =getInstallDataTime();
	ptime t2 =from_ftime<ptime>(ft1);
	CPPUNIT_ASSERT(t1 == t2);
	}
}

void InstallDateTest::TestGetInstallDateFromRegistry() {
	using namespace software_encrypt;
	using namespace boost::posix_time;
	SYSTEMTIME st = {0};
	FILETIME ft = {0};

	{
	memset(&st, 0, sizeof(st));
	st.wYear = 2009;
	st.wMonth = 5;
	st.wDay = 8;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDataOnRegistry(ft);
	ptime t1 = internal_utility::getInstallDateFromRegistry();
	ptime t2 =from_ftime<ptime>(ft);
	CPPUNIT_ASSERT(t1 == t2);
	}
	
	{
	// 如果是一个不存在的日期，应该返回今天才对
	memset(&st, 0, sizeof(st));
	st.wYear = 2009;
	st.wMonth = 5;
	st.wDay = 18;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDataOnRegistry(ft);
	ptime t1 = internal_utility::getInstallDateFromRegistry();
	ptime t2 =from_ftime<ptime>(ft);
	CPPUNIT_ASSERT(t1 == t2);
	}

	{
	// 如果是一个不存在的日期，应该返回今天才对
	// 如果对一个错误的日期进行SystemTimeToFileTime, 
	// 他会返回0， 并且放回上一次正确的结果(MS)
	// 说一这个测试用例仍然是对的
	memset(&st, 0, sizeof(st));
	st.wYear = 2009;
	st.wMonth = 13;
	st.wDay = 18;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDataOnRegistry(ft);
	ptime t1 = internal_utility::getInstallDateFromRegistry();
	ptime t2 =from_ftime<ptime>(ft);
	CPPUNIT_ASSERT(t1 == t2);
	}
}

void InstallDateTest::TestGetInstallDateFromWin() {
	using namespace software_encrypt;
	using namespace boost::posix_time;
	SYSTEMTIME st = {0};
	FILETIME ft = {0};
 
	{
	memset(&st, 0, sizeof(st));
	st.wYear = 2009;
	st.wMonth = 5;
	st.wDay = 8;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDateInWin(ft);
	ptime t1 = internal_utility::getInstallDateFromWin();
	ptime t2 =from_ftime<ptime>(ft);
	CPPUNIT_ASSERT(t1 == t2);
	}
}
void InstallDateTest::TestGetInstallDateFromFile() {
	using namespace software_encrypt;
	using namespace boost::posix_time;
	SYSTEMTIME st = {0};
	FILETIME ft = {0};

	{
	memset(&st, 0, sizeof(st));
	st.wYear = 2009;
	st.wMonth = 5;
	st.wDay = 8;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDateFile(ft);
	ptime t1 = internal_utility::getInstallDateFromFile();
	ptime t2 =from_ftime<ptime>(ft);
	CPPUNIT_ASSERT(t1 == t2);
	}
}

SYSTEMTIME st_from_tm(const tm &t) {
	SYSTEMTIME rt = {0};
	rt.wYear = t.tm_year + 1900;
	rt.wMonth = t.tm_mon+1;
	rt.wDay = t.tm_mday;
	rt.wHour = t.tm_hour;
	rt.wMinute = t.tm_min;
	rt.wSecond = t.tm_sec;
	return rt;
}

