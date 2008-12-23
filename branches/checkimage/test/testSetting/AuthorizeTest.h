#ifndef _TEST_SETTING_AUTHORIZETEST_H__
#define _TEST_SETTING_AUTHORIZETEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class AuthorizeTest : public CPPUNIT_NS::TestFixture {
public:
	AuthorizeTest(void);
	~AuthorizeTest(void);

	CPPUNIT_TEST_SUITE(AuthorizeTest);
	CPPUNIT_TEST(TestCheckPassword);
	CPPUNIT_TEST(TestChangePassword);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestCheckPassword();
	void TestChangePassword();
};

#endif  // _TEST_SETTING_AUTHORIZETEST_H__
