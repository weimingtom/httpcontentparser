#include "StdAfx.h"
#include ".\contentsettingtest.h"
#include <contentchecksetting.h>
#include <webcontenttype.h>

ContentSettingTest::ContentSettingTest(void) {
}

ContentSettingTest::~ContentSettingTest(void) {
}


//===========================
//
void ContentSettingTest::TestEnableCheck() {
}
void ContentSettingTest::TestTwoWrong() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	SettingItem::setModified(false);
	ContentCheckSetting contentSetting;
	contentSetting.enableCheck(IMAGE_TYPE_BMP, true);
	contentSetting.enableCheck(IMAGE_TYPE_JPEG, true);
	contentSetting.enableCheck(IMAGE_TYPE_GIF, false);
	contentSetting.enableCheck(IMAGE_TYPE_PNG, false);
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	CPPUNIT_ASSERT(true == contentSetting.needCheck(IMAGE_TYPE_BMP));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(IMAGE_TYPE_JPEG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(IMAGE_TYPE_GIF));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(IMAGE_TYPE_PNG));
}
void ContentSettingTest::TestTwoModel() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	ContentCheckSetting contentSetting;
	SettingItem::setModified(false);
	contentSetting.enableCheck(CONTYPE_HTML, true);
	contentSetting.enableCheck(CONTYPE_PNG, true);
	contentSetting.enableCheck(CONTYPE_XML, true);
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_XML));

	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_XML));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_XML));
}
void ContentSettingTest::TestNeedCheck() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	ContentCheckSetting contentSetting;
	contentSetting.enableCheck(CONTYPE_HTML, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(true == contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(CONTYPE_PNG, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(CONTYPE_XML, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, false);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_BMP, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_BMP));
	CPPUNIT_ASSERT(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_JPG, true);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_JPG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_BMP));
}