#pragma once

#include <cppunit/extensions/HelperMacros.h>

class FilterSettingTest : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(FilterSettingTest);
	CPPUNIT_TEST(addBlackDNS);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual void setUp();
	virtual void tearDown();

protected:
	void addBlackDNS();

public:
	FilterSettingTest(void);
	~FilterSettingTest(void);
};
