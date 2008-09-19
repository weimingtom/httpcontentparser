// WebHistoryRecorder.cpp : CWebHistoryRecorder µÄÊµÏÖ

#include "stdafx.h"
#include "WebHistoryRecorder.h"
#include "globalvariable.h"
#include <webhistoryrecordersetting.h>
#include ".\webhistoryrecorder.h"
#include <typeconvert.h>

// CWebHistoryRecorder

STDMETHODIMP CWebHistoryRecorder::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWebHistoryRecorder
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


//===============================================
// Pages
STDMETHODIMP CWebHistoryRecorder::get_RecordPronPages(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordPornPages();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPronPages(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordPornPages(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllPages(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordAllPages();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllPages(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordAllPages(convert(newVal));
	return S_OK;
}

//===============================================
// Images
STDMETHODIMP CWebHistoryRecorder::get_RecordPornImage(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordPornImage();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPornImage(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordPornImage(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllImage(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordAllImage();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllImage(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordAllImage(convert(newVal));
	return S_OK;
}


//================================================
// Websites


STDMETHODIMP CWebHistoryRecorder::get_RecordPornWebsite(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordPornWebsite();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPornWebsite(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordPornWebsite(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllWebsite(VARIANT_BOOL* pVal)
{
	*pVal = g_webhistoryRecordSetting_.recordAllWebsite();
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllWebsite(VARIANT_BOOL newVal)
{
	g_webhistoryRecordSetting_.recordAllWebsite(convert(newVal));
	return S_OK;
}
