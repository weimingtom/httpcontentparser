#include "StdAfx.h"
#include ".\appcontroltest.h"
#include <setting\programcontrol.h>
#include <utility\strutility.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

// 注意必须有顺序
#define ITEM_FILE_1	TEXT("C:\\WINDOWS\\system32\\accwiz.exe")
#define ITEM_FILE_2	TEXT("C:\\WINDOWS\\system32\\actmovie.exe")
#define ITEM_FILE_3	TEXT("C:\\WINDOWS\\system32\\alg.exe")
#define ITEM_FILE_4	TEXT("C:\\WINDOWS\\system32\\attrib.exe")
#define ITEM_FILE_5	TEXT("C:\\WINDOWS\\system32\\ciadv.msc")

void testAppConrol() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	ProgramControl controler;
	controler.addItem(ITEM_FILE_1);
	controler.addItem(ITEM_FILE_2);
	controler.addItem(ITEM_FILE_3);
	controler.addItem(ITEM_FILE_4);

	BOOST_CHECK(true == controler.check(ITEM_FILE_5));
	BOOST_CHECK(false == controler.check(ITEM_FILE_1));
	BOOST_CHECK(false == controler.check(ITEM_FILE_2));
	BOOST_CHECK(false == controler.check(ITEM_FILE_3));
	BOOST_CHECK(false == controler.check(ITEM_FILE_4));

	const TCHAR * p[] = {ITEM_FILE_1, ITEM_FILE_2,  ITEM_FILE_3, ITEM_FILE_4, ITEM_FILE_5};

	// TODO: 目前FILENO里面没有属性值
	strutility::_tstring cur, next;
	ProgramControl::FILEINFO * info;
	int cnt = 0;
	int result = controler.getFirstItem(&cur, &info);
	while (result != 0) {
		BOOST_CHECK(0 == _tcscmp(p[cnt++], cur.c_str()));

		result = controler.getNextItem(cur, &next, &info);
		cur = next;
	}

	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(SettingItem::MODE_PARENT == SettingItem::getModel());
	BOOST_CHECK(true == controler.check(ITEM_FILE_5));
	BOOST_CHECK(true == controler.check(ITEM_FILE_1));
	BOOST_CHECK(true == controler.check(ITEM_FILE_2));
	BOOST_CHECK(true == controler.check(ITEM_FILE_3));
	BOOST_CHECK(true == controler.check(ITEM_FILE_4));

	SettingItem::setModel(SettingItem::MODE_CHILD);
}