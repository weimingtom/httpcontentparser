#ifndef _TEST_SETTING_CALCULARGRAPH_TEST_H__
#define _TEST_SETTING_CALCULARGRAPH_TEST_H__

#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

class CalculargraphTest  : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(CalculargraphTest);
	CPPUNIT_TEST(TestCulargraph);
	CPPUNIT_TEST(TestMultiCalculargraph);
	CPPUNIT_TEST_SUITE_END();

public:
	void TestCulargraph();
	void TestMultiCalculargraph();
public:
	CalculargraphTest(void);
	~CalculargraphTest(void);
};

#endif  // _TEST_SETTING_CALCULARGRAPH_TEST_H__