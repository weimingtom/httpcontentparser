#ifndef _TEST_FILTER_SETTING_IACCESSNETWORKTEST_H__
#define _TEST_FILTER_SETTING_IACCESSNETWORKTEST_H__


#include <cppunit/extensions/HelperMacros.h>

class IAccessNetworkTest : public CPPUNIT_NS::TestFixture {
public:
	IAccessNetworkTest(void);
	~IAccessNetworkTest(void);

	CPPUNIT_TEST_SUITE(IAccessNetworkTest);
	CPPUNIT_TEST(TestTwoModel);
	CPPUNIT_TEST(TestSetAndGetBlockTime);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestSetAndGetBlockTime();
	void TestTwoModel();
};

#endif  // _TEST_FILTER_SETTING_IACCESSNETWORKTEST_H__