#ifndef _TEST_FILTERSETTING_ISEACHRULETEST_H__
#define _TEST_FILTERSETTING_ISEACHRULETEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ISeachRuleTest : public CPPUNIT_NS::TestFixture {
public:
	ISeachRuleTest(void);
	~ISeachRuleTest(void);

	CPPUNIT_TEST_SUITE(ISeachRuleTest);
	CPPUNIT_TEST(TestISeachRule);
	CPPUNIT_TEST_SUITE_END();
protected:
	void TestISeachRule();
};

#endif  // _TEST_FILTERSETTING_ISEACHRULETEST_H__