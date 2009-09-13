#include "StdAfx.h"
#include ".\contentsettingtest.h"
#include <setting\contentchecksetting.h>
#include <webcontenttype.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

//===========================
//
void TestEnableCheck() {
}
void TestTwoWrong() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	SettingItem::setModified(false);
	ContentCheckSetting contentSetting;
	contentSetting.enableCheck(IMAGE_TYPE_BMP, true);
	contentSetting.enableCheck(IMAGE_TYPE_JPEG, true);
	contentSetting.enableCheck(IMAGE_TYPE_GIF, false);
	contentSetting.enableCheck(IMAGE_TYPE_PNG, false);
	BOOST_CHECK( true == SettingItem::isModified());

	BOOST_CHECK(true == contentSetting.needCheck(IMAGE_TYPE_BMP));
	BOOST_CHECK(true == contentSetting.needCheck(IMAGE_TYPE_JPEG));
	BOOST_CHECK(false == contentSetting.needCheck(IMAGE_TYPE_GIF));
	BOOST_CHECK(false == contentSetting.needCheck(IMAGE_TYPE_PNG));
}
void TestTwoModel() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	ContentCheckSetting contentSetting;
	SettingItem::setModified(false);
	contentSetting.enableCheck(CONTYPE_HTML, true);
	contentSetting.enableCheck(CONTYPE_PNG, true);
	contentSetting.enableCheck(CONTYPE_XML, true);
	BOOST_CHECK( true == SettingItem::isModified());

	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_XML));

	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_XML));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_XML));
}
void TestNeedCheck() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	ContentCheckSetting contentSetting;
	contentSetting.enableCheck(CONTYPE_HTML, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(true == contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(CONTYPE_PNG, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(CONTYPE_XML, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_XML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, false);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_XML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_XML, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_XML));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_BMP, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_XML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_BMP));
	BOOST_CHECK(false == contentSetting.needCheck(CONTYPE_JPG));

	contentSetting.enableCheck(CONTYPE_JPG, true);
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_JPG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_HTML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_PNG));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_XML));
	BOOST_CHECK(contentSetting.needCheck(CONTYPE_BMP));
}