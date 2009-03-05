#ifndef _TESTSETTING_APPCONTROLTEST_H__
#define _TESTSETTING_APPCONTROLTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class AppControlTest   : public CPPUNIT_NS::TestFixture {
public:
	AppControlTest(void);
	~AppControlTest(void);

public:
	CPPUNIT_TEST_SUITE(AppControlTest);
	CPPUNIT_TEST(testAppConrol);
	CPPUNIT_TEST_SUITE_END();

private:
	void testAppConrol();
};

#endif  // _TESTSETTING_APPCONTROLTEST_H__
