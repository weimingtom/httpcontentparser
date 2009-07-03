// SearchRule.cpp : CSearchRule 的实现

#include "stdafx.h"
#include ".\searchrule.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <utility\strutility.h>
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
	// 如果不可用直接退出
	if (false == g_configuration.getSearchRule()->isEnabled()) {
		*pass = VARIANT_TRUE;
	}

	const int buffer_length = 1024;
	char mcbs[buffer_length] = {0};

	// 处理search word, 如果search  word是一个UTF8串	
	_bstr_t bstrWord = search_word;
	const char * utf8 = (char*)bstrWord;
	const int search_word_len = strlen(utf8);

	// 如果搜索词汇过长，则直接退出
	if (search_word_len > buffer_length) {
		*pass = VARIANT_TRUE;
	}

	char  buffer[buffer_length] = {0};
	strutility::extUTF8FromStr(utf8, buffer,  search_word_len);
	strutility::utf8ToDBCS(buffer, mcbs, search_word_len);

	bool passed = g_configuration.getSearchRule()->check((TCHAR*)bstr_t(host_name), mcbs);
	*pass = convert(passed);

	// 记录
	const int buf_size = 512;
	char main_name[buf_size];
	get_main_dns_name(main_name, buf_size, (TCHAR*)_bstr_t(host_name));

	// 只有当工作在child模式下载， 才进行转换
	if (SettingItem::MODE_PARENT != SettingItem::getModel()) {
		g_searchwordUtil.addKeyword(std::string(mcbs), getSearchEngineType(main_name));
	}

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
