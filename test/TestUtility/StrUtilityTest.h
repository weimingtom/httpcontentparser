#ifndef _TEST_UTILITY_STR_UTILITY_H__
#define _TEST_UTILITY_STR_UTILITY_H__

#include <cppunit/extensions/HelperMacros.h>


class StrUtilityTest  : public CPPUNIT_NS::TestFixture  {
public:
	StrUtilityTest(void);
	~StrUtilityTest(void);

public:
	CPPUNIT_TEST_SUITE(StrUtilityTest);
	CPPUNIT_TEST(TestSplitString);
	CPPUNIT_TEST(Teststrnstr);
	CPPUNIT_TEST(TestEndWith);
	CPPUNIT_TEST(Test_extract_string);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestSplitString();
	void Teststrnstr();
	void Test_extract_string();
	void TestEndWith();
};

#endif  // _TEST_UTILITY_STR_UTILITY_H__