#include "StdAfx.h"
#include ".\iseachruletest.h"
#include ".\comtestutility.h"
#include <utility\dns.h>
#include <utility\strutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <comdef.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void TestRemove() {
	GetInChildMode();

	AutoInitInScale auto_;
	ISearchRule * seachrule = NULL;
	CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seachrule);
	
	_bstr_t test_string("xxxxxxxxxxxxxxx");
	
	// 获取主机地址
	TCHAR *seach1 = TEXT("google.com"), *seach2 = TEXT("baidu.com");
	TCHAR seach_name1[MAX_PATH], seach_name2[MAX_PATH];
	get_main_dns_name(seach_name1, MAX_PATH, seach1);
	get_main_dns_name(seach_name2, MAX_PATH, seach2);

	// 测试用例
	VARIANT_BOOL passed;
	seachrule->addBlackSeachword(test_string);
	seachrule->enableCheckSeachEngine(_bstr_t(seach_name1), VARIANT_TRUE);
	seachrule->enableCheckSeachEngine(_bstr_t(seach_name2), VARIANT_FALSE);
	seachrule->check(test_string,  _bstr_t(seach_name1), &passed);
	BOOST_ASSERT (VARIANT_FALSE == passed);
	seachrule->check(test_string,  _bstr_t(seach_name2),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	seachrule->removeBlackSeachWord(test_string);
	seachrule->check(test_string,  _bstr_t(seach_name2),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);
	seachrule->check(test_string,  _bstr_t(seach_name1), &passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);
}
void TestISeachRule() {
	GetInChildMode();

	AutoInitInScale auto_;
	ISearchRule * seachrule = NULL;
	CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seachrule);
	
	_bstr_t test_string("xxxxxxxxxxxxxxx");
	_bstr_t test_string_none("xxxxxxxxxxxxxxx___");

	// 获取主机地址
	TCHAR *seach1 = TEXT("google.com"), *seach2 = TEXT("baidu.com");
	TCHAR seach_name1[MAX_PATH], seach_name2[MAX_PATH];
	get_main_dns_name(seach_name1, MAX_PATH, seach1);
	get_main_dns_name(seach_name2, MAX_PATH, seach2);

	// 测试用例
	VARIANT_BOOL passed;
	seachrule->addBlackSeachword(test_string);
	seachrule->enableCheckSeachEngine(_bstr_t(seach_name1), VARIANT_TRUE);
	seachrule->enableCheckSeachEngine(_bstr_t(seach_name2), VARIANT_FALSE);

	seachrule->check(test_string,  _bstr_t(seach_name1), &passed);
	BOOST_ASSERT (VARIANT_FALSE == passed);

	seachrule->check(test_string,  _bstr_t(seach_name2),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	seachrule->check(test_string_none, _bstr_t(seach_name1),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	seachrule->enableCheckSeachEngine(_bstr_t(seach_name1), VARIANT_FALSE);

	seachrule->check(test_string, _bstr_t(seach_name1),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	seachrule->check(test_string_none, _bstr_t(seach_name1),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	seachrule->check(test_string_none, _bstr_t(seach_name2),&passed);
	BOOST_ASSERT (VARIANT_TRUE == passed);

	SafeRelease(seachrule);
}
