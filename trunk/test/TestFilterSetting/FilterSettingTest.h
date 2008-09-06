#ifndef _TEST_FILTER_SETTING_FILTERSETTINGTEST_H__
#define _TEST_FILTER_SETTING_FILTERSETTINGTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class FilterSettingTest : public CPPUNIT_NS::TestFixture {
public:
	CPPUNIT_TEST_SUITE(FilterSettingTest);
	CPPUNIT_TEST(TestaddBlackDNS);
	CPPUNIT_TEST(TestcheckDNS);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual void setUp();
	virtual void tearDown();

protected:
	void TestcheckDNS();
	void TestaddBlackDNS();
public:
	FilterSettingTest(void);
	~FilterSettingTest(void);
};

#endif  // _TEST_FILTER_SETTING_FILTERSETTINGTEST_H__