#include "StdAfx.h"
#include ".\iseachruletest.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <comdef.h>

ISeachRuleTest::ISeachRuleTest(void)
{
}

ISeachRuleTest::~ISeachRuleTest(void)
{
}


void ISeachRuleTest::TestRemove() {
	AutoInitInScale auto_;
	ISearchRule * seachrule = NULL;
	CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seachrule);
	
	_bstr_t test_string("xxxxxxxxxxxxxxx");
	VARIANT_BOOL passed;
	seachrule->addBlackSeachword(test_string);
	seachrule->enableCheckSeachEngine(_bstr_t("google.com"), VARIANT_TRUE);
	seachrule->enableCheckSeachEngine(_bstr_t("baidu.com"), VARIANT_FALSE);
	seachrule->check(test_string,  _bstr_t("seach.google.com"), &passed);
	CPPUNIT_ASSERT (VARIANT_FALSE == passed);
	seachrule->check(test_string,  _bstr_t("www.baidu.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

	seachrule->removeBlackSeachWord(test_string);
	seachrule->check(test_string,  _bstr_t("www.baidu.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);
	seachrule->check(test_string,  _bstr_t("seach.google.com"), &passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);
}
void ISeachRuleTest::TestISeachRule() {
	AutoInitInScale auto_;
	ISearchRule * seachrule = NULL;
	CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seachrule);
	
	_bstr_t test_string("xxxxxxxxxxxxxxx");
	_bstr_t test_string_none("xxxxxxxxxxxxxxx___");

	VARIANT_BOOL passed;
	seachrule->addBlackSeachword(test_string);
	seachrule->enableCheckSeachEngine(_bstr_t("google.com"), VARIANT_TRUE);
	seachrule->enableCheckSeachEngine(_bstr_t("baidu.com"), VARIANT_FALSE);
	seachrule->check(test_string,  _bstr_t("seach.google.com"), &passed);
	CPPUNIT_ASSERT (VARIANT_FALSE == passed);
	seachrule->check(test_string,  _bstr_t("www.baidu.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

	seachrule->check(test_string_none, _bstr_t("google.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

	seachrule->enableCheckSeachEngine(_bstr_t("google.com"), VARIANT_FALSE);

	seachrule->check(test_string, _bstr_t("google.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

	seachrule->check(test_string_none, _bstr_t("google.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

		seachrule->check(test_string_none, _bstr_t("baidu.com"),&passed);
	CPPUNIT_ASSERT (VARIANT_TRUE == passed);

	SafeRelease(seachrule);
}
