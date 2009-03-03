// WebContentRecord.cpp : CWebContentRecord µÄÊµÏÖ

#include "stdafx.h"
#include "WebContentRecord.h"
#include ".\webcontentrecord.h"
#include ".\globalvariable.h"
#include <string>
#include <comutil.h>

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
	} else {
		*keyword = _bstr_t("");
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
	} else {
		*keyword = _bstr_t("");
	}
	return S_OK;
}
