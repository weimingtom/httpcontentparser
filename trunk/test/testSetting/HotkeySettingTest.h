#ifndef _TEST_SETTING_HOTKEYSETTINGTEST_H__
#define _TEST_SETTING_HOTKEYSETTINGTEST_H__


#include <cppunit/extensions/HelperMacros.h>

class HotkeySettingTest : public CPPUNIT_NS::TestFixture {
public:
	HotkeySettingTest(void);
	~HotkeySettingTest(void);

	CPPUNIT_TEST_SUITE(HotkeySettingTest);
	CPPUNIT_TEST(testHotkey);
	CPPUNIT_TEST_SUITE_END();
private:
	void testHotkey();
};

#endif  // _TEST_SETTING_HOTKEYSETTINGTEST_H__