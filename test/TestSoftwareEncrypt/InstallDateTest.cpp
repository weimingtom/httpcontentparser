#include "StdAfx.h"
#include ".\installdatetest.h"
#include <softwareencrypt\installdate.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <time.h>

InstallDateTest::InstallDateTest(void) {
} 

InstallDateTest::~InstallDateTest(void) {
}

namespace {
	SYSTEMTIME st_from_tm(const tm &t);
};


void InstallDateTest::TestInstallDateItem() {
	using namespace software_encrypt;
	setInstall();
	std::cout<<"Install date: " << getInstallData() << std::endl;
	std::cout<<"Installed days : " << getInstalledDays() <<std::endl;
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
	tm rt = to_tm(t1);
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
	tm rt = to_tm(t1);
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
	tm rt = to_tm(t1);
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
	std::cout<<"pWin: " << to_simple_string(t1)<< std::endl;
	std::cout<<"pWin: " << to_simple_string(t2)<< std::endl;
	CPPUNIT_ASSERT(t1 == t2);
	tm rt = to_tm(t1);
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
	std::cout<<"pWin: " << to_simple_string(t1)<< std::endl;
	std::cout<<"pWin: " << to_simple_string(t2)<< std::endl;
	CPPUNIT_ASSERT(t1 == t2);
	tm rt = to_tm(t1);
	}
}

namespace {
	SYSTEMTIME st_from_tm(const tm &t) {
		SYSTEMTIME rt = {0};
		rt.wYear = t.tm_year;
		rt.wMonth = t.tm_mon;
		rt.wDay = t.tm_mday;
		rt.wHour = t.tm_hour;
		rt.wMinute = t.tm_min;
		rt.wSecond = t.tm_sec;
		rt.wDay = t.tm_wday;
		return rt;
	}
}

