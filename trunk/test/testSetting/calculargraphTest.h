#ifndef _TEST_SETTING_CALCULARGRAPH_TEST_H__
#define _TEST_SETTING_CALCULARGRAPH_TEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class CalculargraphTest  : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(CalculargraphTest);
	CPPUNIT_TEST(TestForceswitch);
	CPPUNIT_TEST(TestSetASmallerTime);
	CPPUNIT_TEST(TestCulargraph);
	CPPUNIT_TEST(testMulitSetTimeLeft);
	CPPUNIT_TEST(testMultiStopTimer);
	CPPUNIT_TEST(testCalarStopTimer);
	CPPUNIT_TEST(TestSetTimeEscape);
	CPPUNIT_TEST(TestMultiCalculargraph);
	CPPUNIT_TEST_SUITE_END();

public:
	void TestForceswitch();
	void TestSetASmallerTime();
	void TestCulargraph();
	void testCalarStopTimer();
	void testMulitSetTimeLeft();
	void testMultiStopTimer();
	void TestMultiCalculargraph();
	void TestSetTimeEscape();
public:
	CalculargraphTest(void);
	~CalculargraphTest(void);
};

#endif  // _TEST_SETTING_CALCULARGRAPH_TEST_H__