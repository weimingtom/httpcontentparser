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


void EyecareTest::TestPassword() {
	// 设置原始密码
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting(&authorize);
	setting.initialize();

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
}
