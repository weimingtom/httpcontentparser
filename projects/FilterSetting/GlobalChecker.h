// GlobalChecker.h : CGlobalChecker µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ
#include "FilterSetting.h"


// CGlobalChecker
class ATL_NO_VTABLE CGlobalChecker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGlobalChecker, &CLSID_GlobalChecker>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGlobalChecker, &IID_IGlobalChecker, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CGlobalChecker() 	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GLOBALCHECKER)


BEGIN_COM_MAP(CGlobalChecker)
	COM_INTERFACE_ENTRY(IGlobalChecker)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() {
		return S_OK;
	}
	
	void FinalRelease() {
	}

public:
	STDMETHOD(checkDNS)(BSTR dns, VARIANT_BOOL* enabled);
	STDMETHOD(checkContent)(LONG type, CHAR data[ ], LONG num, VARIANT_BOOL* passed);
	STDMETHOD(needCheck)(LONG type, VARIANT_BOOL* needed);
	STDMETHOD(checkImage)(LONG type, LONG* action_code);
	STDMETHOD(checkIP)(BSTR ipAddress, VARIANT_BOOL* enabled);
};

OBJECT_ENTRY_AUTO(__uuidof(GlobalChecker), CGlobalChecker)
