#ifndef _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__
#define _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__

#include "stdafx.h"
#include <windows.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class InstallDateTest : public CPPUNIT_NS::TestFixture {
public:
	InstallDateTest(void);
	~InstallDateTest(void);

	CPPUNIT_TEST_SUITE(InstallDateTest);
	CPPUNIT_TEST(TestInstallDateItem);
	CPPUNIT_TEST(TestGetInstallDateFromRegistry);
	CPPUNIT_TEST(TestGetInstallDateFromFile);
	CPPUNIT_TEST(TestGetInstallDateFromWin);
	CPPUNIT_TEST_SUITE_END();

private:
	void TestInstallDateItem();
	void TestGetInstallDateFromRegistry();
	void TestGetInstallDateFromFile();
	void TestGetInstallDateFromWin();

private:
	boost::posix_time::ptime rawdate; //
};

SYSTEMTIME st_from_tm(const tm &t);

#endif  // _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__