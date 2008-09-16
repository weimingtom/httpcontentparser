#include "StdAfx.h"
#include ".\onlinehoursettingtest.h"
#include <onlinehoursetting.h>
#include <assert.h>

OnlineHourSettingTest::OnlineHourSettingTest(void) {
}

OnlineHourSettingTest::~OnlineHourSettingTest(void) {
}


//=================================================

void OnlineHourSettingTest::TestOnlineHour() {
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

	online_hour.enableOnlineHour(false);
	CPPUNIT_ASSERT(online_hour.isEnabled() == false);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enableOnlineHour(true);
	CPPUNIT_ASSERT(online_hour.isEnabled() == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	CPPUNIT_ASSERT(online_hour.getHour(1, 1) == true);
	CPPUNIT_ASSERT(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);
}

