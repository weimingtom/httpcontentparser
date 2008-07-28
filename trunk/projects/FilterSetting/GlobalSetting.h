// GlobalSetting.h : CGlobalSetting 的声明

#pragma once
#include "resource.h"       // 主符号

#include "FilterSetting.h"


// CGlobalSetting

class ATL_NO_VTABLE CGlobalSetting : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGlobalSetting, &CLSID_GlobalSetting>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGlobalSetting, &IID_IGlobalSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CGlobalSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GLOBALSETTING)


BEGIN_COM_MAP(CGlobalSetting)
	COM_INTERFACE_ENTRY(IGlobalSetting)
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
	// 增加
	STDMETHOD(addBlackDNS)(BSTR dns);
	STDMETHOD(addWhiteDNS)(BSTR dns);
	STDMETHOD(removeBlackDNS)(BSTR blackDNS);
	STDMETHOD(removeWhiteDNS)(BSTR whiteDNS);
	STDMETHOD(enableDNSCheck)(VARIANT_BOOL enable);

	// image
	STDMETHOD(enableImageCheck)(int type, VARIANT_BOOL check);
	STDMETHOD(enableShowImage)(VARIANT_BOOL show);
};

OBJECT_ENTRY_AUTO(__uuidof(GlobalSetting), CGlobalSetting)
