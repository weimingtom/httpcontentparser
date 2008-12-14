// WebContentCheck.h : CWebContentCheck µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CWebContentCheck

class ATL_NO_VTABLE CWebContentCheck : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebContentCheck, &CLSID_WebContentCheck>,
	public ISupportErrorInfo,
	public IDispatchImpl<IWebContentCheck, &IID_IWebContentCheck, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWebContentCheck()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WEBCONTENTCHECK)


BEGIN_COM_MAP(CWebContentCheck)
	COM_INTERFACE_ENTRY(IWebContentCheck)
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
	STDMETHOD(shouldCheck)(LONG type, VARIANT_BOOL* check);
	STDMETHOD(setCheckScope)(LONG min, LONG max);
	STDMETHOD(enableCheck)(VARIANT_BOOL enabled, LONG type);
	STDMETHOD(shouldCheckBySize)(LONG size, VARIANT_BOOL* check);
};

OBJECT_ENTRY_AUTO(__uuidof(WebContentCheck), CWebContentCheck)
