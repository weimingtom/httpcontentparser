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

void EyecareTest::TestTimeSetting() {
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERTAINMENT_TIME);

	setting.setEntertainTime(60);
	setting.setRestTime(60);
	
	int a = setting.getRemainTime();
	CPPUNIT_ASSERT(setting.getRemainTime() > 0);
	CPPUNIT_ASSERT(setting.getRemainTime() > 0);
}
void EyecareTest::TestPassword() {
	// 设置原始密码
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	// 使用错误的密码转换， 状态不会改变
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);

	// 使用正确的密码
	CPPUNIT_ASSERT(setting.switchState(supassword) == EyecareSetting::ENTERTAINMENT_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);

	// 从ENTERTAINMENT_Time转变不需要改变密码
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
}

void EyecareTest::TestSwitchState() {
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERTAINMENT_TIME);
	setting.setRestTime(2);
	setting.setEntertainTime(5);

	// 正常切换
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == EyecareSetting::ENTERTAINMENT_TIME);
	Sleep(6000);
	int x = setting.getRemainTime();
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(2400);
	x = setting.getRemainTime();
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);
}

void EyecareTest::TextForceSwitch() {
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	const int restTime = 1;
	const int entertain = 1;
	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERTAINMENT_TIME);
	setting.setRestTime(restTime);
	setting.setEntertainTime(entertain);
	setting.setPasswordType(PASSWORD_SU);

	// 正常切换
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	Sleep(1000 * (restTime+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);


	// 强制锁定
	setting.ForceLockWnd();
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);

	// 使用密码释放
	CPPUNIT_ASSERT (setting.switchState("123") == EyecareSetting::ENTERTAINMENT_TIME);
	Sleep(1000 * (restTime+1));
	CPPUNIT_ASSERT (setting.trySwitch() ==true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);	
}