// SearchRule.cpp : CSearchRule 的实现

#include "stdafx.h"
#include ".\searchrule.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <utility\dns.h>
#include <searchengine_define.h>
#include <comutil.h>

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

STDMETHODIMP CSearchRule::check(BSTR search_word, BSTR host_name, VARIANT_BOOL* pass)
{
	bool passed = g_configuration.getSearchRule()->check((TCHAR*)bstr_t(host_name), (TCHAR*)bstr_t(search_word));
	*pass = convert(passed);

	// 记录
	const int buf_size = 512;
	char main_name[buf_size];
	get_main_dns_name(main_name, buf_size, (TCHAR*)_bstr_t(host_name));

	g_searchwordUtil.addKeyword(std::string((TCHAR*)_bstr_t(search_word)), getSearchEngineType(main_name));

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

STDMETHODIMP CSearchRule::isSettingEnabled(BSTR searchengine, VARIANT_BOOL* isSettingenabled)
{
	*isSettingenabled = convert(g_configuration.getSearchRule()->setting_shouldCheck((TCHAR*)_bstr_t(searchengine)));
	return S_OK;
}

STDMETHODIMP CSearchRule::getFirstSearchWord(BSTR* first)
{
	*first = _bstr_t(g_configuration.getSearchRule()->getFirstSearchWord().c_str());
	return S_OK;
}

STDMETHODIMP CSearchRule::getNextSearchWord(BSTR cur, BSTR* next)
{
	*next = _bstr_t(g_configuration.getSearchRule()->getNextSearchWord((TCHAR*)_bstr_t(cur)).c_str());
	return S_OK;
}
