// Authorize.h : CAuthorize µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CAuthorize

class ATL_NO_VTABLE CAuthorize : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAuthorize, &CLSID_Authorize>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAuthorize, &IID_IAuthorize, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAuthorize() {
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AUTHORIZE)


BEGIN_COM_MAP(CAuthorize)
	COM_INTERFACE_ENTRY(IAuthorize)
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

	STDMETHOD(checkPassword)(BSTR password, VARIANT_BOOL* bSuccess);
};

OBJECT_ENTRY_AUTO(__uuidof(Authorize), CAuthorize)
