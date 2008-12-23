#include "StdAfx.h"
#include ".\autocleantest.h"
#include <autoclean.h>
#include <atltime.h>

AutocleanTest::AutocleanTest(void) {
}

AutocleanTest::~AutocleanTest(void) {
}


void AutocleanTest::testAutoclean() {
	AutoClean autoclean;
	CTime t = CTime::GetCurrentTime();
	TCHAR buffer[MAX_PATH];

	// …Ë÷√ ±º‰
	_sntprintf(buffer, MAX_PATH, "%04d-%02d-%02d %02d:%02d", 
		t.GetYear(), t.GetMonth(), t.GetDay()-1,
		t.GetHour(), t.GetMinute());
	autoclean.setLastTime(buffer);

	SettingItem::setModified(false);
	autoclean.setTimespan(3);
	CPPUNIT_ASSERT(true == SettingItem::isModified());
	CPPUNIT_ASSERT(false == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.setTimespan(2);
	CPPUNIT_ASSERT(true == SettingItem::isModified());
	CPPUNIT_ASSERT(false == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.setTimespan(1);
	CPPUNIT_ASSERT(true == SettingItem::isModified());
	CPPUNIT_ASSERT(true == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.reset();
	autoclean.setTimespan(1);
	CPPUNIT_ASSERT(true == SettingItem::isModified());
	CPPUNIT_ASSERT(false == autoclean.shouldExec());

}