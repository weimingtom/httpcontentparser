// GlobalChecker.h : CGlobalChecker 的声明

#pragma once
#include "resource.h"       // 主符号
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
	// 增加
	STDMETHOD(addBlackDNS)(BSTR dns);
	STDMETHOD(addWhiteDNS)(BSTR dns);
	STDMETHOD(removeBlackDNS)(BSTR blackDNS);
	STDMETHOD(removeWhiteDNS)(BSTR whiteDNS);

	STDMETHOD(enableDNSCheck)(VARIANT_BOOL enable);

	STDMETHOD(showImage)(VARIANT_BOOL* showed);
	STDMETHOD(checkImage)(int type, VARIANT_BOOL* checked);
	STDMETHOD(enableImageCheck)(int type, VARIANT_BOOL check);
	STDMETHOD(enableShowImage)(VARIANT_BOOL show);
	STDMETHOD(checkDNS)(BSTR dns, VARIANT_BOOL* enabled);
};

OBJECT_ENTRY_AUTO(__uuidof(GlobalChecker), CGlobalChecker)
