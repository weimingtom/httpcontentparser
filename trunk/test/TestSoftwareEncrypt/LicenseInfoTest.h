#ifndef _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__
#define _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__


#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class LicenseInfoTest : public CPPUNIT_NS::TestFixture {
public:
	LicenseInfoTest(void);
	~LicenseInfoTest(void);

	CPPUNIT_TEST_SUITE(LicenseInfoTest);
	CPPUNIT_TEST(testSNStored);
	CPPUNIT_TEST(testReg);
	CPPUNIT_TEST_SUITE_END();

private:
	void testSNStored();
	void testReg();
};

#endif  // _TESTSOFTWAREENCRYPT_LICENSEINFOTEST_H__
