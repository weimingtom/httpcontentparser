#ifndef _TEST_SOFTWARE_ENCRYPT_BASEENCRYPTTEST_H__
#define _TEST_SOFTWARE_ENCRYPT_BASEENCRYPTTEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class BaseEncryptTest : public CPPUNIT_NS::TestFixture  {
public:
	BaseEncryptTest(void);
	~BaseEncryptTest(void);

	CPPUNIT_TEST_SUITE(BaseEncryptTest);
	CPPUNIT_TEST(TestBaseEncry);
	CPPUNIT_TEST_SUITE_END();

private:
	void TestBaseEncry();
};

#endif  // _TEST_SOFTWARE_ENCRYPT_BASEENCRYPTTEST_H__