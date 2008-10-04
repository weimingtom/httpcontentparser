#ifndef _TEST_SETTING_SEARCHRULETEST_H__
#define _TEST_SETTING_SEARCHRULETEST_H__

#include <cppunit/extensions/HelperMacros.h>

class SearchRuleTest : public CPPUNIT_NS::TestFixture {
public:
	SearchRuleTest(void);
	~SearchRuleTest(void);

public:
	CPPUNIT_TEST_SUITE(SearchRuleTest);
	CPPUNIT_TEST(TestSeachRuleSetting);
	CPPUNIT_TEST(TestSeachEnabled);
	CPPUNIT_TEST(TestParentChildMode);
	CPPUNIT_TEST_SUITE_END();

protected:
	void TestSeachRuleSetting();
	void TestSeachEnabled();
	void TestParentChildMode();
};

#endif  // _TEST_SETTING_SEARCHRULETEST_H__