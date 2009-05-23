#ifndef _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__
#define _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__


#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

class LicenseInfoTest : public CPPUNIT_NS::TestFixture {
public:
	LicenseInfoTest(void);
	~LicenseInfoTest(void);


	CPPUNIT_TEST_SUITE(LicenseInfoTest);
	CPPUNIT_TEST(testInstallDate);
	CPPUNIT_TEST(testSNStored);
	CPPUNIT_TEST(testReg);
	CPPUNIT_TEST_SUITE_END();

private:
	void testSNStored();
	void testReg();
	void testInstallDate();

	std::string rawSN1;
	boost::posix_time::ptime rawdate; 
};

#endif  // _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__
