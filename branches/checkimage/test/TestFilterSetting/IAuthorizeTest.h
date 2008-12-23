#ifndef _TEST_FILTER_SETTING_IAUTHORIZETEST_H__
#define _TEST_FILTER_SETTING_IAUTHORIZETEST_H__

#include <cppunit/extensions/HelperMacros.h>

class IAuthorizeTest  : public CPPUNIT_NS::TestFixture  {
public:
	CPPUNIT_TEST_SUITE(IAuthorizeTest);
	CPPUNIT_TEST(testCheckPassword);
	CPPUNIT_TEST_SUITE_END();

protected:
	void testCheckPassword();
public:
	IAuthorizeTest(void);
	~IAuthorizeTest(void); 
};

#endif  // _TEST_FILTER_SETTING_IAUTHORIZETEST_H__
