#include "StdAfx.h"
#include ".\webhistoryrecordtest.h"
#include <webhistoryrecordersetting.h>
#include <settingitem.h>

using namespace CPPUNIT_NS;

WebHistoryRecordTest::WebHistoryRecordTest(void) {
}

WebHistoryRecordTest::~WebHistoryRecordTest(void) {
}

// ��������ģʽ
void WebHistoryRecordTest::TestParentMode() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == false);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == false);

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	// �����еĿ�Ӵ��
	web_history.recordAllImage(true);
	web_history.recordAllPages(true);
	web_history.recordAllWebsite(true);
	CPPUNIT_ASSERT(web_history.recordAllImage() == true);
	CPPUNIT_ASSERT(web_history.recordAllPages() == true);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == true);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	// �л�ģʽ
	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == false);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == false);

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(web_history.recordAllImage() == true);
	CPPUNIT_ASSERT(web_history.recordAllPages() == true);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == true);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);
}

void WebHistoryRecordTest::TestRegular() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	web_history.enable(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == false);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == false);

	web_history.enable(true);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);
}
void WebHistoryRecordTest::TestEnable() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	web_history.recordAllImage(true);
	web_history.recordAllPages(true);
	web_history.recordAllWebsite(true);

	CPPUNIT_ASSERT(web_history.recordAllImage() == true);
	CPPUNIT_ASSERT(web_history.recordAllPages() == true);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == true);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);


	web_history.recordAllImage(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == true);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == true);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	web_history.recordAllPages(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == true);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	web_history.recordAllWebsite(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	web_history.recordPornImage(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);

	web_history.recordPornWebsite(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == false);

	web_history.recordPornPages(false);
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == false);
	CPPUNIT_ASSERT(web_history.recordPornPages() == false);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == false);
}

void WebHistoryRecordTest::TestDefault() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	WebHistoryRecorderSetting web_history;
	CPPUNIT_ASSERT(web_history.recordAllImage() == false);
	CPPUNIT_ASSERT(web_history.recordAllPages() == false);
	CPPUNIT_ASSERT(web_history.recordAllWebsite() == false);
	CPPUNIT_ASSERT(web_history.recordPornImage() == true);
	CPPUNIT_ASSERT(web_history.recordPornPages() == true);
	CPPUNIT_ASSERT(web_history.recordPornWebsite() == true);
}