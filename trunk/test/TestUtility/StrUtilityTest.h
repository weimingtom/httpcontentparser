#ifndef _TEST_UTILITY_STR_UTILITY_H__
#define _TEST_UTILITY_STR_UTILITY_H__

#include <cppunit/extensions/HelperMacros.h>


class StrUtilityTest  : public CPPUNIT_NS::TestFixture  {
public:
	StrUtilityTest(void);
	~StrUtilityTest(void);

public:
	CPPUNIT_TEST_SUITE(StrUtilityTest);
	CPPUNIT_TEST(Teststrnstr);
	CPPUNIT_TEST_SUITE_END();
private:
	void Teststrnstr();
};

#endif  // _TEST_UTILITY_STR_UTILITY_H__