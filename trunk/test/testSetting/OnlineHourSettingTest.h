#ifndef _TEST_SETTING_ONLINEHOURSETTINGTEST_H__
#define _TEST_SETTING_ONLINEHOURSETTINGTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class OnlineHourSettingTest : public CPPUNIT_NS::TestFixture {
public:
	OnlineHourSettingTest(void);
	~OnlineHourSettingTest(void);

public:
	CPPUNIT_TEST_SUITE(OnlineHourSettingTest);
	CPPUNIT_TEST(TestOnlineHour);
	CPPUNIT_TEST_SUITE_END();
private:
	void TestOnlineHour();
};

#endif  // _TEST_SETTING_ONLINEHOURSETTINGTEST_H__
