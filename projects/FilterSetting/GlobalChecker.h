// GlobalChecker.h : CGlobalChecker ������

#pragma once
#include "resource.h"       // ������
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
	// ����
	STDMETHOD(addBlackDNS)(BSTR dns);
	STDMETHOD(addWhiteDNS)(BSTR dns);
	STDMETHOD(removeBlackDNS)(BSTR blackDNS);
	STDMETHOD(removeWhiteDNS)(BSTR whiteDNS);
	STDMETHOD(enableDNSCheck)(VARIANT_BOOL enable);
};

OBJECT_ENTRY_AUTO(__uuidof(GlobalChecker), CGlobalChecker)
