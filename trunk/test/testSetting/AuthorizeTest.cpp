#include "StdAfx.h"
#include ".\authorizetest.h"
#include <setting\authorize.h>
#include <string>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;
using namespace std;


void TestCheckPassword() {
	Authorize authorize;
	const int type1 = 1;
	const string password1 = "hello", fakepassword1 = "idje", newpassword="idjf";
	BOOST_CHECK( true == authorize.setNewPassword(password1, type1));
	BOOST_CHECK( true == SettingItem::isModified());
#ifndef _DEBUG
	// 此行代码在Debug模式下会出现assert
	BOOST_CHECK( false == authorize.setNewPassword(password1, type1));
#endif

	BOOST_CHECK( true == authorize.checkPassword(password1, type1));

	// 修改密码
	SettingItem::setModified(false);
	BOOST_CHECK( false == authorize.setPassword(newpassword, fakepassword1, type1));
	BOOST_CHECK( false == SettingItem::isModified());
	BOOST_CHECK( true == authorize.setPassword(newpassword, password1, type1));
	BOOST_CHECK( true == SettingItem::isModified());


	BOOST_CHECK( false == authorize.checkPassword(password1, type1));
	BOOST_CHECK( false == authorize.checkPassword(fakepassword1, type1));
	BOOST_CHECK( true == authorize.checkPassword(newpassword, type1));

	// 多个密码
	const int type2 = 2;
	const string password2 = "hellijd_*fo", fakepassword2 = "idjasdfasde", newpassword2="idjeovo1912+0d*f";
	BOOST_CHECK( true == authorize.setNewPassword(password2, type2));
#ifndef _DEBUG
	// 此行代码在Debug模式下会出现assert
	BOOST_CHECK( false == authorize.setNewPassword(password2, type2));
#endif

	BOOST_CHECK( true == authorize.checkPassword(password2, type2));

	// 设置密吗
	SettingItem::setModified(false);
	BOOST_CHECK( false == authorize.setPassword(newpassword2, fakepassword2, type2));
	BOOST_CHECK( false == SettingItem::isModified());
	BOOST_CHECK( true == authorize.setPassword(newpassword2, password2, type2));
	BOOST_CHECK( true == SettingItem::isModified());

	BOOST_CHECK( false == authorize.checkPassword(password2, type2));
	BOOST_CHECK( false == authorize.checkPassword(fakepassword2, type2));
	BOOST_CHECK( true == authorize.checkPassword(newpassword2, type2));
}
void TestChangePassword() {
}
