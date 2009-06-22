#include "StdAfx.h"
#include ".\eyecaretest.h"
#include <eyecaresetting.h>
#include <passwordtype.h>
#include <authorize.h>
#include <string>

using namespace std;
using namespace CPPUNIT_NS;

EyecareTest::EyecareTest(void) {
}

EyecareTest::~EyecareTest(void) {
}

void EyecareTest::TestModelsInParentAndChild() {
	// 无论是在那种模式下， 用户的状态都不会改变
	// 该是什么状态就是什么状态
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));
	
	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);
	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);
	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);
}
void EyecareTest::TestSetLeft() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);

	SettingItem::setModified(false);
	setting.setEnterTime(60);
	setting.setEyecareTime(60);
	CPPUNIT_ASSERT(true == SettingItem::isModified());
	
	SettingItem::setModified(false);
	CPPUNIT_ASSERT(setting.getRemainTime() > 0);
	CPPUNIT_ASSERT(false == SettingItem::isModified());

	// 注意设置剩余时间不应视为修改文件，否则修改的就太频繁了 ;(
	// 此项应该在程序结束的时候存储，或其他项存储的时候进行存储
	SettingItem::setModified(false);
	setting.setLeftTime(20);
	CPPUNIT_ASSERT(false == SettingItem::isModified());

	Sleep(1000);
	CPPUNIT_ASSERT(setting.getRemainTime() < 20);
}

void EyecareTest::TestTimeSetting() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);

	setting.setEnterTime(60);
	setting.setEyecareTime(60);
	
	int a = setting.getRemainTime();
	CPPUNIT_ASSERT(setting.getRemainTime() > 0);
	CPPUNIT_ASSERT(setting.getRemainTime() > 0);
}
void EyecareTest::TestPassword() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	// 设置原始密码
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	// 使用错误的密码转换， 状态不会改变
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);

	// 使用正确的密码
	CPPUNIT_ASSERT(setting.switchState(supassword) == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);

	// 从ENTERT_TIME转变不需要改变密码
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
}

void EyecareTest::TestSwitchState() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(2);
	setting.setEnterTime(5);

	// 正常切换
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == EyecareSetting::ENTERT_TIME);
	Sleep(6000);
	int x = setting.getRemainTime();
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(2400);
	x = setting.getRemainTime();
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
}

void EyecareTest::TestMultiModelSwitch() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(1);
	setting.setEnterTime(1);

	// 初始状态ENTERT_TIME
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::ENTERT_TIME);

	// 经过一段时间可以成功转换装在
	Sleep(1200);
	CPPUNIT_ASSERT(true == setting.trySwitch());
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);	
	Sleep(200);
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);	// 时间不长， 不会切换状态
	Sleep(200);
	CPPUNIT_ASSERT(false == setting.trySwitch());
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);

	// 经过一段时间可以成功转换装在
	Sleep(800);
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT(true == setting.trySwitch());
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::ENTERT_TIME);
	SettingItem::setModel(SettingItem::MODE_CHILD);
}
void EyecareTest::TestAfterModelSwitch() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(2);
	setting.setEnterTime(5);

	// 首先设置转变状态为“充值计时器”
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	setting.switchState("123");		// 进入EYECARE_MODE
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	setting.switchState("123");		// 结束"EYECARE", 此时只是重置计时器 
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	// 至其为"进入管理员状态"
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_ENTERSU);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);

	// 进入EYECARE_MODE
	setting.switchState("123");
	setting.switchState("123"); 
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT(SettingItem::MODE_PARENT == SettingItem::getModel());

	SettingItem::setModel(SettingItem::MODE_CHILD);
}