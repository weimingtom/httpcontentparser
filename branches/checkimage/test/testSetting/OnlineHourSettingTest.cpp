#include "StdAfx.h"
#include ".\onlinehoursettingtest.h"
#include <onlinehoursetting.h>
#include <assert.h>

OnlineHourSettingTest::OnlineHourSettingTest(void) {
}

OnlineHourSettingTest::~OnlineHourSettingTest(void) {
}


//=================================================

// 测试父子模式的切换
void OnlineHourSettingTest::TestTowModeSwitched() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	OnlineHourSetting online_hour;
	CPPUNIT_ASSERT(online_hour.isEnabled() == true);

	online_hour.setHour(1, 0, true);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, true);

	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.setHour(1, 0, false);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, false);


	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	online_hour.enable(false);
	CPPUNIT_ASSERT(online_hour.isEnabled() == false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	CPPUNIT_ASSERT(online_hour.isEnabled() == false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	SettingItem::setModel(SettingItem::MODE_CHILD);
	online_hour.enable(false);
	CPPUNIT_ASSERT(online_hour.isEnabled() == false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	CPPUNIT_ASSERT(online_hour.isEnabled() == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);
}

void OnlineHourSettingTest::TestOnlineHour() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	OnlineHourSetting online_hour;
	CPPUNIT_ASSERT(online_hour.isEnabled() == true);

	online_hour.setHour(1, 0, true);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, true);

	SettingItem::setModified(false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);
	CPPUNIT_ASSERT( false == SettingItem::isModified());

	SettingItem::setModified(false);
	online_hour.setHour(1, 0, false);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, false);
	CPPUNIT_ASSERT( true == SettingItem::isModified());


	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);

	online_hour.enable(false);
	CPPUNIT_ASSERT(online_hour.isEnabled() == false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	CPPUNIT_ASSERT(online_hour.isEnabled() == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);
}

