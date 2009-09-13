#include "StdAfx.h"
#include ".\autocleantest.h"
#include <setting\autoclean.h>
#include <atltime.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void testAutoclean() {
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
	BOOST_CHECK(true == SettingItem::isModified());
	BOOST_CHECK(false == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.setTimespan(2);
	BOOST_CHECK(true == SettingItem::isModified());
	BOOST_CHECK(false == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.setTimespan(1);
	BOOST_CHECK(true == SettingItem::isModified());
	BOOST_CHECK(true == autoclean.shouldExec());
	
	SettingItem::setModified(false);
	autoclean.reset();
	autoclean.setTimespan(1);
	BOOST_CHECK(true == SettingItem::isModified());
	BOOST_CHECK(false == autoclean.shouldExec());

}