#include "StdAfx.h"
#include ".\webhistoryrecordtest.h"
#include <setting\webhistoryrecordersetting.h>
#include <setting\settingitem.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


// 测试两种模式
void TestParentMode() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;

	SettingItem::setModified(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);
	BOOST_CHECK(false == SettingItem::isModified());

	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == false);
	BOOST_CHECK(web_history.recordPornWebsite() == false);
	BOOST_CHECK(false == SettingItem::isModified());

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);
	BOOST_CHECK(false == SettingItem::isModified());

	// 是所有的可哟个
	web_history.recordAllImage(true);
	web_history.recordAllPages(true);
	web_history.recordAllWebsite(true);
	BOOST_CHECK(true == SettingItem::isModified());
	BOOST_CHECK(web_history.recordAllImage() == true);
	BOOST_CHECK(web_history.recordAllPages() == true);
	BOOST_CHECK(web_history.recordAllWebsite() == true);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);

	// 切换模式
	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == false);
	BOOST_CHECK(web_history.recordPornWebsite() == false);

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(web_history.recordAllImage() == true);
	BOOST_CHECK(web_history.recordAllPages() == true);
	BOOST_CHECK(web_history.recordAllWebsite() == true);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);
}

void TestRegular() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	web_history.enable(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == false);
	BOOST_CHECK(web_history.recordPornWebsite() == false);

	web_history.enable(true);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);
}
void TestEnable() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	web_history.recordAllImage(true);
	web_history.recordAllPages(true);
	web_history.recordAllWebsite(true);

	BOOST_CHECK(web_history.recordAllImage() == true);
	BOOST_CHECK(web_history.recordAllPages() == true);
	BOOST_CHECK(web_history.recordAllWebsite() == true);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);


	web_history.recordAllImage(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == true);
	BOOST_CHECK(web_history.recordAllWebsite() == true);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);

	web_history.recordAllPages(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == true);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);

	web_history.recordAllWebsite(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);

	web_history.recordPornImage(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);

	web_history.recordPornWebsite(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == false);

	web_history.recordPornPages(false);
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == false);
	BOOST_CHECK(web_history.recordPornPages() == false);
	BOOST_CHECK(web_history.recordPornWebsite() == false);
}

void TestDefault() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	BOOST_CHECK(web_history.recordAllImage() == false);
	BOOST_CHECK(web_history.recordAllPages() == false);
	BOOST_CHECK(web_history.recordAllWebsite() == false);
	BOOST_CHECK(web_history.recordPornImage() == true);
	BOOST_CHECK(web_history.recordPornPages() == true);
	BOOST_CHECK(web_history.recordPornWebsite() == true);
}