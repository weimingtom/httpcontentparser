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
	// ������������ģʽ�£� �û���״̬������ı�
	// ����ʲô״̬����ʲô״̬
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

	// ע������ʣ��ʱ�䲻Ӧ��Ϊ�޸��ļ��������޸ĵľ�̫Ƶ���� ;(
	// ����Ӧ���ڳ��������ʱ��洢����������洢��ʱ����д洢
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
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

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

void EyecareTest::TestMultiModelSwitch() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	CPPUNIT_ASSERT(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::ENTERT_TIME);
	setting.setEyecareTime(1);
	setting.setEnterTime(1);

	// ��ʼ״̬ENTERT_TIME
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::ENTERT_TIME);

	// ����һ��ʱ����Գɹ�ת��װ��
	Sleep(1200);
	CPPUNIT_ASSERT(true == setting.trySwitch());
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);	
	Sleep(200);
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);	// ʱ�䲻���� �����л�״̬
	Sleep(200);
	CPPUNIT_ASSERT(false == setting.trySwitch());
	CPPUNIT_ASSERT(setting.getState() == EyecareSetting::EYECARE_TIME);

	// ����һ��ʱ����Գɹ�ת��װ��
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

	// ��������ת��״̬Ϊ����ֵ��ʱ����
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	setting.switchState("123");		// ����EYECARE_MODE
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::EYECARE_TIME);
	setting.switchState("123");		// ����"EYECARE", ��ʱֻ�����ü�ʱ�� 
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	// ����Ϊ"�������Ա״̬"
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_ENTERSU);
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);

	// ����EYECARE_MODE
	setting.switchState("123");
	setting.switchState("123"); 
	CPPUNIT_ASSERT (setting.getState() == EyecareSetting::ENTERT_TIME);
	CPPUNIT_ASSERT(SettingItem::MODE_PARENT == SettingItem::getModel());

	SettingItem::setModel(SettingItem::MODE_CHILD);
}