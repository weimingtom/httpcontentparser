#pragma once


#include <cppunit/extensions/HelperMacros.h>

class EyecareTest : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(EyecareTest);
	CPPUNIT_TEST(getTimeLeft);
	CPPUNIT_TEST_SUITE_END();

public:
	void getTimeLeft();
public:
	EyecareTest(void);
	~EyecareTest(void);
};
