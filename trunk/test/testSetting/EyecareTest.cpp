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
	// ����ԭʼ����
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(supassword, PASSWORD_SU));
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting(&authorize);
	setting.initialize();

	// ʹ�ô��������ת���� ״̬����ı�
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);

	// ʹ����ȷ������
	CPPUNIT_ASSERT(setting.switchState(supassword) == EyecareSetting::ENTERTAINMENT_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERTAINMENT_TIME);

	// ��ENTERTAINMENT_Timeת�䲻��Ҫ�ı�����
	CPPUNIT_ASSERT(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
}

void EyecareTest::TestSwitchState() {
}
