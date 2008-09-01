// WebHistoryRecorder.h : CWebHistoryRecorder µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CWebHistoryRecorder

class ATL_NO_VTABLE CWebHistoryRecorder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebHistoryRecorder, &CLSID_WebHistoryRecorder>,
	public ISupportErrorInfo,
	public IDispatchImpl<IWebHistoryRecorder, &IID_IWebHistoryRecorder, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWebHistoryRecorder()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WEBHISTORYRECORDER)


BEGIN_COM_MAP(CWebHistoryRecorder)
	COM_INTERFACE_ENTRY(IWebHistoryRecorder)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(get_RecordPronPages)(VARIANT_BOOL* pVal);
	STDMETHOD(put_RecordPronPages)(VARIANT_BOOL newVal);
	STDMETHOD(get_RecordAllPages)(VARIANT_BOOL* pVal);
	STDMETHOD(put_RecordAllPages)(VARIANT_BOOL newVal);

	STDMETHOD(get_RecordPornImage)(VARIANT_BOOL* pVal);
	STDMETHOD(put_RecordPornImage)(VARIANT_BOOL newVal);
	STDMETHOD(get_RecordAllImage)(VARIANT_BOOL* pVal);
	STDMETHOD(put_RecordAllImage)(VARIANT_BOOL newVal);

	STDMETHOD(get_recordPornWebsite)(VARIANT_BOOL* pVal);
	STDMETHOD(put_recordPornWebsite)(VARIANT_BOOL newVal);
	STDMETHOD(get_recordAllWebsite)(VARIANT_BOOL* pVal);
	STDMETHOD(put_recordAllWebsite)(VARIANT_BOOL newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(WebHistoryRecorder), CWebHistoryRecorder)
