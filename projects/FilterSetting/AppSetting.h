// AppSetting.h : CAppSetting µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CAppSetting

class ATL_NO_VTABLE CAppSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppSetting, &CLSID_AppSetting>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAppSetting, &IID_IAppSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAppSetting() {
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPSETTING)


BEGIN_COM_MAP(CAppSetting)
	COM_INTERFACE_ENTRY(IAppSetting)
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

	STDMETHOD(setHotkey)(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess);
	STDMETHOD(GetInstallPath)(BSTR* path);
	STDMETHOD(switchModel)(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc);
	STDMETHOD(get_ParentModel)(VARIANT_BOOL* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(AppSetting), CAppSetting)
