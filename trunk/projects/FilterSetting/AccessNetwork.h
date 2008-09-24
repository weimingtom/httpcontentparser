// AccessNetwork.h : CAccessNetwork µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CAccessNetwork

class ATL_NO_VTABLE CAccessNetwork : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAccessNetwork, &CLSID_AccessNetwork>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAccessNetwork, &IID_IAccessNetwork, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAccessNetwork()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACCESSNETWORK)


BEGIN_COM_MAP(CAccessNetwork)
	COM_INTERFACE_ENTRY(IAccessNetwork)
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

	STDMETHOD(accessNetwork)(VARIANT_BOOL* bAccessable);
	STDMETHOD(setBlockTime)(LONG day, LONG hour);
	STDMETHOD(removeBlockTime)(LONG day, LONG hour);
};

OBJECT_ENTRY_AUTO(__uuidof(AccessNetwork), CAccessNetwork)
