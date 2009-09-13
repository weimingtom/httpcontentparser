#include "StdAfx.h"
#include ".\onlinehoursettingtest.h"
#include <setting\onlinehoursetting.h>
#include <assert.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


//=================================================

// 测试父子模式的切换
void TestTowModeSwitched() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	OnlineHourSetting online_hour;
	BOOST_CHECK(online_hour.isEnabled() == true);

	online_hour.setHour(1, 0, true);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, true);

	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.setHour(1, 0, false);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, false);


	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	online_hour.enable(false);
	BOOST_CHECK(online_hour.isEnabled() == false);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	BOOST_CHECK(online_hour.isEnabled() == false);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	SettingItem::setModel(SettingItem::MODE_CHILD);
	online_hour.enable(false);
	BOOST_CHECK(online_hour.isEnabled() == false);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	BOOST_CHECK(online_hour.isEnabled() == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);
}

void TestOnlineHour() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	OnlineHourSetting online_hour;
	BOOST_CHECK(online_hour.isEnabled() == true);

	online_hour.setHour(1, 0, true);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, true);

	SettingItem::setModified(false);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);
	BOOST_CHECK( false == SettingItem::isModified());

	SettingItem::setModified(false);
	online_hour.setHour(1, 0, false);
	online_hour.setHour((DWORD)MAKELPARAM(1,1), true);
	online_hour.setHour(1, 2, false);
	BOOST_CHECK( true == SettingItem::isModified());


	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);

	online_hour.enable(false);
	BOOST_CHECK(online_hour.isEnabled() == false);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == true);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == true);

	online_hour.enable(true);
	BOOST_CHECK(online_hour.isEnabled() == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,0)) == false);
	BOOST_CHECK(online_hour.getHour(1, 1) == true);
	BOOST_CHECK(online_hour.getHour((DWORD)MAKELPARAM(1,2)) == false);
}

