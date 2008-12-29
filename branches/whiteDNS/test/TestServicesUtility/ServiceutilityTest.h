#ifndef _SERVICE_UTILITY_SERVICEUTILITYTEST_H__
#define _SERVICE_UTILITY_SERVICEUTILITYTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ServiceutilityTest : public CPPUNIT_NS::TestFixture {
public:
	ServiceutilityTest(void);
	~ServiceutilityTest(void);

	CPPUNIT_TEST_SUITE(ServiceutilityTest);
	CPPUNIT_TEST(TestCheckSeachRule);
	CPPUNIT_TEST_SUITE_END();
protected:
	void TestCheckSeachRule();
};

#endif  // _SERVICE_UTILITY_SERVICEUTILITYTEST_H__