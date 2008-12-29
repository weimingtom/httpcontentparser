// SearchRule.cpp : CSearchRule µÄÊµÏÖ

#include "stdafx.h"
#include ".\searchrule.h"
#include ".\globalvariable.h"
#include <typeconvert.h>

// CSearchRule

STDMETHODIMP CSearchRule::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISearchRule
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSearchRule::check(BSTR seach_word, BSTR host_name, VARIANT_BOOL* pass)
{
	bool passed = g_configuration.getSearchRule()->check((TCHAR*)bstr_t(host_name), (TCHAR*)bstr_t(seach_word));
	*pass = convert(passed);

	return S_OK;
}

STDMETHODIMP CSearchRule::addBlackSeachword(BSTR seachword) {
	 g_configuration.getSearchRule()->addBlackSearchWord((char*)_bstr_t(seachword));
	return S_OK;
}

STDMETHODIMP CSearchRule::enableCheckSeachEngine(BSTR seachengine, VARIANT_BOOL enabled) {
	 g_configuration.getSearchRule()->enableCheck((char*)_bstr_t(seachengine), convert(enabled));
	return S_OK;
}

STDMETHODIMP CSearchRule::removeBlackSeachWord(BSTR blackword) {
	g_configuration.getSearchRule()->removeBlackSeachWord((char*)_bstr_t(blackword));
	return S_OK;
}
