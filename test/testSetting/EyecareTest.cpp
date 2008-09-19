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
	// ����ԭʼ����
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	// ʹ�ô��������ת���� ״̬����ı�
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);

	// ʹ����ȷ������
	CPPUNIT_ASSERT(setting.switchState(supassword) == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);

	// ��ENTERT_TIMEת�䲻��Ҫ�ı�����
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
}

void EyecareTest::TestSwitchState() {
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(2);
	setting.setEnterTime(5);

	// �����л�
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

void EyecareTest::TextForceSwitch() {
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	const int restTime = 1;
	const int entertain = 1;
	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(restTime);
	setting.setEnterTime(entertain);
	setting.setPasswordType(PASSWORD_SU);

	// �����л�
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	Sleep(1000 * (restTime+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);


	// ǿ������
	setting.ForceLockWnd();
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == false);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.trySwitch() == false);

	// ʹ�������ͷ�
	CPPUNIT_ASSERT (setting.switchState("123") == EyecareSetting::ENTERT_TIME);
	Sleep(1000 * (restTime+1));
	CPPUNIT_ASSERT (setting.trySwitch() ==true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	Sleep(1000 * (entertain+1));
	CPPUNIT_ASSERT (setting.trySwitch() == true);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);	
}