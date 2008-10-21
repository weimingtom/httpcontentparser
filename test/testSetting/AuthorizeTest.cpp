#include "StdAfx.h"
#include ".\authorizetest.h"
#include <authorize.h>
#include <string>

using namespace std;

AuthorizeTest::AuthorizeTest(void) {
}

AuthorizeTest::~AuthorizeTest(void) {
}

void AuthorizeTest::TestCheckPassword() {
	Authorize authorize;
	const int type1 = 1;
	const string password1 = "hello", fakepassword1 = "idje", newpassword="idjf";
	CPPUNIT_ASSERT( true == authorize.setNewPassword(password1, type1));
	CPPUNIT_ASSERT( true == SettingItem::isModified());
#ifndef _DEBUG
	// ���д�����Debugģʽ�»����assert
	CPPUNIT_ASSERT( false == authorize.setNewPassword(password1, type1));
#endif

	CPPUNIT_ASSERT( true == authorize.checkPassword(password1, type1));

	// �޸�����
	SettingItem::setModified(false);
	CPPUNIT_ASSERT( false == authorize.setPassword(newpassword, fakepassword1, type1));
	CPPUNIT_ASSERT( false == SettingItem::isModified());
	CPPUNIT_ASSERT( true == authorize.setPassword(newpassword, password1, type1));
	CPPUNIT_ASSERT( true == SettingItem::isModified());


	CPPUNIT_ASSERT( false == authorize.checkPassword(password1, type1));
	CPPUNIT_ASSERT( false == authorize.checkPassword(fakepassword1, type1));
	CPPUNIT_ASSERT( true == authorize.checkPassword(newpassword, type1));

	// �������
	const int type2 = 2;
	const string password2 = "hellijd_*fo", fakepassword2 = "idjasdfasde", newpassword2="idjeovo1912+0d*f";
	CPPUNIT_ASSERT( true == authorize.setNewPassword(password2, type2));
#ifndef _DEBUG
	// ���д�����Debugģʽ�»����assert
	CPPUNIT_ASSERT( false == authorize.setNewPassword(password2, type2));
#endif

	CPPUNIT_ASSERT( true == authorize.checkPassword(password2, type2));

	// ��������
	SettingItem::setModified(false);
	CPPUNIT_ASSERT( false == authorize.setPassword(newpassword2, fakepassword2, type2));
	CPPUNIT_ASSERT( false == SettingItem::isModified());
	CPPUNIT_ASSERT( true == authorize.setPassword(newpassword2, password2, type2));
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	CPPUNIT_ASSERT( false == authorize.checkPassword(password2, type2));
	CPPUNIT_ASSERT( false == authorize.checkPassword(fakepassword2, type2));
	CPPUNIT_ASSERT( true == authorize.checkPassword(newpassword2, type2));
}
void AuthorizeTest::TestChangePassword() {
}
