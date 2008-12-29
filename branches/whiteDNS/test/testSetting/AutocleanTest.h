#ifndef _TEST_SETTING_AUTOCLEANTEST_H__
#define _TEST_SETTING_AUTOCLEANTEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class AutocleanTest : public CPPUNIT_NS::TestFixture {
public:
	AutocleanTest(void);
	~AutocleanTest(void);

	CPPUNIT_TEST_SUITE(AutocleanTest);
	CPPUNIT_TEST(testAutoclean);
	CPPUNIT_TEST_SUITE_END();
private:
	void testAutoclean();
};

#endif  // _TEST_SETTING_AUTOCLEANTEST_H__