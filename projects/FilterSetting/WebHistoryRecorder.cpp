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
STDMETHODIMP CWebHistoryRecorder::get_RecordPornPages(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordPornPages());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPornPages(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordPornPages(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllPages(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordAllPages());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllPages(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordAllPages(convert(newVal));
	return S_OK;
}

//===============================================
// Images
STDMETHODIMP CWebHistoryRecorder::get_RecordPornImage(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordPornImage());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPornImage(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordPornImage(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllImage(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordAllImage());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllImage(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordAllImage(convert(newVal));
	return S_OK;
}


//================================================
// Websites


STDMETHODIMP CWebHistoryRecorder::get_RecordPornURLs(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordPornWebsite());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordPornURLs(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordPornWebsite(convert(newVal));
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::get_RecordAllURLs(VARIANT_BOOL* pVal)
{
	*pVal = convert(g_configuration.getWebHistoryRecordSetting()->recordAllWebsite());
	return S_OK;
}

STDMETHODIMP CWebHistoryRecorder::put_RecordAllURLs(VARIANT_BOOL newVal)
{
	g_configuration.getWebHistoryRecordSetting()->recordAllWebsite(convert(newVal));
	return S_OK;
}
