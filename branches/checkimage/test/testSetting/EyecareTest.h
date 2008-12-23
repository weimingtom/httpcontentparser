#ifndef _TESTSETTING_EYECARETEST_H__
#define _TESTSETTING_EYECARETEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class EyecareTest : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(EyecareTest);
	CPPUNIT_TEST(TestAfterModelSwitch);
	CPPUNIT_TEST(TestSetLeft);
	CPPUNIT_TEST(TestTimeSetting);
	CPPUNIT_TEST(TestPassword);
	CPPUNIT_TEST(TestSwitchState);
	CPPUNIT_TEST_SUITE_END();

private:	
	void TextForceSwitch();
	void TestPassword();
	void TestSwitchState();
	void TestTimeSetting();
	void TestSetLeft();
	void TestAfterModelSwitch();
public:
	EyecareTest(void);
	~EyecareTest(void);
};


#endif   // _TESTSETTING_EYECARETEST_H__