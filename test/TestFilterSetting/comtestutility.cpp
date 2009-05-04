
#include "StdAfx.h"
#include ".\comtestutility.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>

bool isRunOnParentModel() {
	AutoInitInScale auot;
	ISnowmanSetting *appsetting = NULL;
	CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appsetting);
	VARIANT_BOOL result;
	appsetting->get_ParentModel(&result);
	return convert(result);
}

void GetInParentModel() {
	AutoInitInScale auot;
	ISnowmanSetting *appsetting = NULL;
	CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appsetting);
	VARIANT_BOOL result;
	appsetting->switchModel(VARIANT_TRUE, _bstr_t("123"), &result);
	assert ( result == VARIANT_TRUE); // ÃÜÂë´íÎó
}

void GetInChildMode() {
	AutoInitInScale auot;
	ISnowmanSetting *appsetting = NULL;
	CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appsetting);
	VARIANT_BOOL result;
	appsetting->switchModel(VARIANT_FALSE, _bstr_t("123"), &result);
	assert ( result == VARIANT_TRUE); // ÃÜÂë´íÎó
}