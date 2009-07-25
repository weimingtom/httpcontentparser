// WebContentRecord.cpp : CWebContentRecord 的实现

#include "stdafx.h"
#include "WebContentRecord.h"
#include ".\webcontentrecord.h"
#include ".\globalvariable.h"
#include <string>
#include <comutil.h>
#include <apputility\apputility.h>

// CWebContentRecord

STDMETHODIMP CWebContentRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWebContentRecord
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CWebContentRecord::SearchKeyword(BSTR keyword, LONG searchEngine)
{
	g_searchwordUtil.addKeyword(std::string((TCHAR*)_bstr_t(keyword)), static_cast<int>(searchEngine));
	return S_OK;
}

STDMETHODIMP CWebContentRecord::GetFirstSearchKeyword(BSTR* keyword, LONG* times, LONG* searchEngine, LONG* timeHighPart, LONG* timeLowPart)
{
	std::string str;
	SeachKeywordUtil::KEYWORD_DATA data;
	if (0 != g_searchwordUtil.getFirst(&str, &data)) {
		*times = static_cast<LONG>(data.seach_count);
		*searchEngine = static_cast<LONG>(data.engine_type);
		*timeHighPart = static_cast<LONG>(data.last_seach.dwHighDateTime);
		*timeLowPart = static_cast<LONG>(data.last_seach.dwLowDateTime);
		*keyword = _bstr_t(str.c_str());
	} else {
		*keyword = _bstr_t("");
		*timeHighPart = 0;
		*timeLowPart  = 0;
	}
	return S_OK;
}

STDMETHODIMP CWebContentRecord::GetNextSearchKeyword(BSTR cur, BSTR* keyword, LONG* times, LONG* searchEngine, LONG* timeHighPart, LONG* timeLowPart)
{
	std::string  next;
	SeachKeywordUtil::KEYWORD_DATA data;
	if (0 != g_searchwordUtil.getNext(std::string((TCHAR*)_bstr_t(cur)), &next, &data)) {
		*keyword = _bstr_t(next.c_str());
		*times = static_cast<LONG>(data.seach_count);
		*searchEngine = static_cast<LONG>(data.engine_type);
		*timeHighPart = static_cast<LONG>(data.last_seach.dwHighDateTime);
		*timeLowPart = static_cast<LONG>(data.last_seach.dwLowDateTime);
		*keyword = _bstr_t(next.c_str());
	} else {
		*timeHighPart = 0;
		*timeLowPart  = 0;
		*keyword = _bstr_t("");
	}
	return S_OK;
}

STDMETHODIMP CWebContentRecord::GetFirstWebsite(BSTR* keyword, LONG* times, LONG* high, LONG* low)
{
	std::string str;
	WebsitesUtil::WEBSITE_DATA data;
	if (0 != g_websitesUtil.getFirst(&str, &data)) {
		*keyword = _bstr_t(str.c_str());
		*times = static_cast<LONG>(data.visit_count);
		*high = static_cast<LONG>(data.latest_visit.dwHighDateTime);
		*low = static_cast<LONG>(data.latest_visit.dwLowDateTime);
	} else {
		*low = 0;
		*high = 0; 
		*keyword = _bstr_t("");
	}

	return S_OK;
}

STDMETHODIMP CWebContentRecord::GetNextWebSite(BSTR cur, BSTR* keyword, LONG* times, LONG* high, LONG* low)
{
	std::string  next;
	_bstr_t current(cur);
	WebsitesUtil::WEBSITE_DATA data;
	if (0 != g_websitesUtil.getNext(std::string((TCHAR*)current), &next, &data) && current.length() > 0) {
		*keyword = _bstr_t(next.c_str());
		*times = static_cast<LONG>(data.visit_count);
		*high = static_cast<LONG>(data.latest_visit.dwHighDateTime);
		*low = static_cast<LONG>(data.latest_visit.dwLowDateTime);
	} else {
		*keyword = _bstr_t("");
		*low = 0;
		*high = 0;
	}
	return S_OK;
}


STDMETHODIMP CWebContentRecord::clearAll(void)
{
	ClearHistory();

	// 清楚内存中保存的记录
	g_searchwordUtil.clear();
	g_websitesUtil.clear();

	return S_OK;
}

STDMETHODIMP CWebContentRecord::clearWebsites(void) {
	g_websitesUtil.clear();
	return S_OK;
}

STDMETHODIMP CWebContentRecord::clearSearchword(void) {
	g_searchwordUtil.clear();
	return S_OK;
}
