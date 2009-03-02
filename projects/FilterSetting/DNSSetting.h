// DNSSetting.h : CDNSSetting µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CDNSSetting

class ATL_NO_VTABLE CDNSSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDNSSetting, &CLSID_DNSSetting>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDNSSetting, &IID_IDNSSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDNSSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DNSSETTING)


BEGIN_COM_MAP(CDNSSetting)
	COM_INTERFACE_ENTRY(IDNSSetting)
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
	STDMETHOD(addBlackDNS)(BSTR dns);
	STDMETHOD(addWhiteDNS)(BSTR dns);
	STDMETHOD(removeBlackDNS)(BSTR blackDNS);
	STDMETHOD(removeWhiteDNS)(BSTR whiteDNS);
	STDMETHOD(enableWhiteDNSCheck)(VARIANT_BOOL enable);
	STDMETHOD(enableBlackDNSCheck)(VARIANT_BOOL enable);
	STDMETHOD(checkDNS)(BSTR dns_name, VARIANT_BOOL* passed);
	STDMETHOD(justEnableWhiteDNS)(VARIANT_BOOL enabled);
	STDMETHOD(isWhiteDNS)(BSTR dns, VARIANT_BOOL* White);
	STDMETHOD(getWhiteDNSCount)(LONG* cnt);
	STDMETHOD(getWhiteDNS)(LONG lIndex, BSTR* dns);

	STDMETHOD(getBlackDNSCount)(LONG* cnt);
	STDMETHOD(getBlackDNS)(LONG lIndex, BSTR* dns);
};

OBJECT_ENTRY_AUTO(__uuidof(DNSSetting), CDNSSetting)
