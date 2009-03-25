#ifndef _TEST_UTILITY_STR_UTILITY_H__
#define _TEST_UTILITY_STR_UTILITY_H__

#include <cppunit/extensions/HelperMacros.h>


class StrUtilityTest  : public CPPUNIT_NS::TestFixture  {
public:
	StrUtilityTest(void);
	~StrUtilityTest(void);

public:
	CPPUNIT_TEST_SUITE(StrUtilityTest);
	CPPUNIT_TEST(TestToLower);
	CPPUNIT_TEST(TestToUpper);
	CPPUNIT_TEST(Test_remove_after);
	CPPUNIT_TEST(TestSplitString);
	CPPUNIT_TEST(Teststrnstr);
	CPPUNIT_TEST(TestEndWith);
	CPPUNIT_TEST(Test_extract_string);
	CPPUNIT_TEST(Test_extUTF8FromStr);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestSplitString();
	void Teststrnstr();
	void Test_extract_string();
	void Test_remove_after();
	void TestEndWith();
	void TestToLower();
	void TestToUpper();
	void Test_extUTF8FromStr();
};

#endif  // _TEST_UTILITY_STR_UTILITY_H__