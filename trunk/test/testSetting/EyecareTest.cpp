#include "StdAfx.h"
#include ".\eyecaretest.h"
#include <setting\eyecaresetting.h>
#include <passwordtype.h>
#include <setting\authorize.h>
#include <string>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;
using namespace std;

void TestModelsInParentAndChild() {
	// 无论是在那种模式下， 用户的状态都不会改变
	// 该是什么状态就是什么状态
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));
	
	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);
	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);
	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);
}
void TestSetLeft() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);

	SettingItem::setModified(false);
	setting.setEnterTime(60);
	setting.setEyecareTime(60);
	BOOST_CHECK(true == SettingItem::isModified());
	
	SettingItem::setModified(false);
	BOOST_CHECK(setting.getRemainTime() > 0);
	BOOST_CHECK(false == SettingItem::isModified());

	// 注意设置剩余时间不应视为修改文件，否则修改的就太频繁了 ;(
	// 此项应该在程序结束的时候存储，或其他项存储的时候进行存储
	SettingItem::setModified(false);
	setting.setLeftTime(20);
	BOOST_CHECK(false == SettingItem::isModified());

	Sleep(1000);
	BOOST_CHECK(setting.getRemainTime() < 20);
}

void TestTimeSetting() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);

	setting.setEnterTime(60);
	setting.setEyecareTime(60);
	
	int a = setting.getRemainTime();
	BOOST_CHECK(setting.getRemainTime() > 0);
	BOOST_CHECK(setting.getRemainTime() > 0);
}
void TestPassword() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	// 设置原始密码
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	// 使用错误的密码转换， 状态不会改变
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);

	// 使用正确的密码
	BOOST_CHECK(setting.switchState(supassword) == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);

	// 从ENTERT_TIME转变不需要改变密码
	BOOST_CHECK(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
}

void TestSwitchState() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(2);
	setting.setEnterTime(5);

	// 正常切换
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK (setting.trySwitch() == EyecareSetting::ENTERT_TIME);
	Sleep(6000);
	int x = setting.getRemainTime();
	BOOST_CHECK (setting.trySwitch() == true);
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(2400);
	x = setting.getRemainTime();
	BOOST_CHECK (setting.trySwitch() == true);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
}

void TestMultiModelSwitch() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(1);
	setting.setEnterTime(1);

	// 初始状态ENTERT_TIME
	BOOST_CHECK(setting.getState() == EyecareSetting::ENTERT_TIME);

	// 经过一段时间可以成功转换装在
	Sleep(1200);
	BOOST_CHECK(true == setting.trySwitch());
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);	
	Sleep(200);
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);	// 时间不长， 不会切换状态
	Sleep(200);
	BOOST_CHECK(false == setting.trySwitch());
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);

	// 经过一段时间可以成功转换装在
	Sleep(800);
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK(true == setting.trySwitch());
	BOOST_CHECK(setting.getState() == EyecareSetting::ENTERT_TIME);
	SettingItem::setModel(SettingItem::MODE_CHILD);
}
void TestAfterModelSwitch() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(2);
	setting.setEnterTime(5);

	// 首先设置转变状态为“充值计时器”
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	setting.switchState("123");		// 进入EYECARE_MODE
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
	setting.switchState("123");		// 结束"EYECARE", 此时只是重置计时器 
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	// 至其为"进入管理员状态"
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_ENTERSU);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);

	// 进入EYECARE_MODE
	setting.switchState("123");
	setting.switchState("123"); 
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK(SettingItem::MODE_PARENT == SettingItem::getModel());

	SettingItem::setModel(SettingItem::MODE_CHILD);
}