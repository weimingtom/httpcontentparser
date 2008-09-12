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
void ContentSettingTest::TestNeedCheck() {
	ContentCheckSetting contentSetting;
	contentSetting.enableCheck(true, CONTYPE_HTML);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	contentSetting.enableCheck(true,CONTYPE_PNG );
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));

	contentSetting.enableCheck(true, CONTYPE_XML);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(false, CONTYPE_XML);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));

	contentSetting.enableCheck(true, CONTYPE_XML);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(true, CONTYPE_XML);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));

	contentSetting.enableCheck(true, CONTYPE_BMP);
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_HTML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_PNG));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_XML));
	CPPUNIT_ASSERT(contentSetting.needCheck(CONTYPE_BMP));
}