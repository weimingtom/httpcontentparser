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
	// ������������ģʽ�£� �û���״̬������ı�
	// ����ʲô״̬����ʲô״̬
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

	// ע������ʣ��ʱ�䲻Ӧ��Ϊ�޸��ļ��������޸ĵľ�̫Ƶ���� ;(
	// ����Ӧ���ڳ��������ʱ��洢����������洢��ʱ����д洢
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

	// ����ԭʼ����
	Authorize authorize;
	string supassword = "123", eyecarePassword = "456";
	BOOST_CHECK(authorize.setNewPassword(eyecarePassword, PASSWORD_EYECARE));

	EyecareSetting setting;
	setting.initialize(&authorize, EyecareSetting::EYECARE_TIME);

	// ʹ�ô��������ת���� ״̬����ı�
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK(setting.switchState(eyecarePassword) == EyecareSetting::EYECARE_TIME);
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);

	// ʹ����ȷ������
	BOOST_CHECK(setting.switchState(supassword) == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);

	// ��ENTERT_TIMEת�䲻��Ҫ�ı�����
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

	// �����л�
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

	// ��ʼ״̬ENTERT_TIME
	BOOST_CHECK(setting.getState() == EyecareSetting::ENTERT_TIME);

	// ����һ��ʱ����Գɹ�ת��װ��
	Sleep(1200);
	BOOST_CHECK(true == setting.trySwitch());
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);	
	Sleep(200);
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);	// ʱ�䲻���� �����л�״̬
	Sleep(200);
	BOOST_CHECK(false == setting.trySwitch());
	BOOST_CHECK(setting.getState() == EyecareSetting::EYECARE_TIME);

	// ����һ��ʱ����Գɹ�ת��װ��
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

	// ��������ת��״̬Ϊ����ֵ��ʱ����
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	setting.switchState("123");		// ����EYECARE_MODE
	BOOST_CHECK (setting.getState() == EyecareSetting::EYECARE_TIME);
	setting.switchState("123");		// ����"EYECARE", ��ʱֻ�����ü�ʱ�� 
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	// ����Ϊ"�������Ա״̬"
	setting.setTerimatedMode(EyecareSetting::EYECARE_TERMIN_ENTERSU);
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);

	// ����EYECARE_MODE
	setting.switchState("123");
	setting.switchState("123"); 
	BOOST_CHECK (setting.getState() == EyecareSetting::ENTERT_TIME);
	BOOST_CHECK(SettingItem::MODE_PARENT == SettingItem::getModel());

	SettingItem::setModel(SettingItem::MODE_CHILD);
}