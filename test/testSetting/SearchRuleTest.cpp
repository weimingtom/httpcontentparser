#include "StdAfx.h"
#include ".\searchruletest.h"
#include <setting\SearchRule.h>
#include <string>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

using namespace std;

//==========================================
// members
void TestSeachRuleSetting() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";

	SettingItem::setModified(false);

	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	BOOST_CHECK(true == SettingItem::isModified());

	SettingItem::setModified(false);
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);
	BOOST_CHECK(true == SettingItem::isModified());

	SettingItem::setModified(false);
	BOOST_CHECK(false == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(false == SettingItem::isModified());


	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);
	BOOST_CHECK(true == SettingItem::isModified());

	SettingItem::setModified(false);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(false == search_rule.check(search_host2, search_word1));

	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(false == SettingItem::isModified());
}

void TestSeachEnabled() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";
	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);

	BOOST_CHECK(false == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));

	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);
	search_rule.enable(false);

	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));

	search_rule.enable(true);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(false == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
}

// 测试父子模式的切换
void TestParentChildMode() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";
	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(false == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));

	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);

	search_rule.enable(false);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));

	search_rule.enable(true);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(false == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));

	SettingItem::setModel(SettingItem::MODE_PARENT);
	search_rule.enable(false);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	search_rule.enable(true);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(false == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));

	search_rule.removeBlackSeachWord(search_word1.c_str());
	SettingItem::setModel(SettingItem::MODE_CHILD);
	search_rule.enable(true);
	BOOST_CHECK(true == search_rule.check(search_host1, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host2, search_word1));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
	BOOST_CHECK(true == search_rule.check(search_host1, no_word));
}