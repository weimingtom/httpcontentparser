#include "StdAfx.h"
#include ".\searchruletest.h"
#include <SearchRule.h>
#include <string>
using namespace std;

SearchRuleTest::SearchRuleTest(void) {
}

SearchRuleTest::~SearchRuleTest(void) {
}

//==========================================
// members
void SearchRuleTest::TestSeachRuleSetting() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";
	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);

	CPPUNIT_ASSERT(false == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));

	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);

	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(false == search_rule.check(search_host2, search_word1));

	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
}

void SearchRuleTest::TestSeachEnabled() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";
	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);

	CPPUNIT_ASSERT(false == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));

	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);
	search_rule.enable(false);

	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));

	search_rule.enable(true);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(false == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
}

// 测试父子模式的切换
void SearchRuleTest::TestParentChildMode() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	const string search_word1 = "hello", no_word="hello2";
	const string search_host1 = "google", search_host2 = "yahoo";
	SearchRule search_rule;
	search_rule.addBlackSearchWord("hello");
	search_rule.addSearchHost(search_host1);
	search_rule.addSearchHost(search_host2);
	search_rule.enableCheck(search_host1, true);
	search_rule.enableCheck(search_host2,  false);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(false == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));

	search_rule.enableCheck(search_host1, false);
	search_rule.enableCheck(search_host2, true);

	search_rule.enable(false);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));

	search_rule.enable(true);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(false == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));

	SettingItem::setModel(SettingItem::MODE_PARENT);
	search_rule.enable(false);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	search_rule.enable(true);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(false == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));

	search_rule.removeBlackSeachWord(search_word1.c_str());
	SettingItem::setModel(SettingItem::MODE_CHILD);
	search_rule.enable(true);
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host2, search_word1));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
	CPPUNIT_ASSERT(true == search_rule.check(search_host1, no_word));
}