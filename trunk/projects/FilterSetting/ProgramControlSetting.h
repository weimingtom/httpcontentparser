// ProgramControlSetting.h : CProgramControlSetting µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"


// CProgramControlSetting

class ATL_NO_VTABLE CProgramControlSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProgramControlSetting, &CLSID_ProgramControlSetting>,
	public IDispatchImpl<IProgramControlSetting, &IID_IProgramControlSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CProgramControlSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROGRAMCONTROLSETTING)


BEGIN_COM_MAP(CProgramControlSetting)
	COM_INTERFACE_ENTRY(IProgramControlSetting)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(AddNewItem)(BSTR path);
	STDMETHOD(GetFirstItem)(BSTR* path);
	STDMETHOD(GetNextItem)(BSTR cur, BSTR* nxt);
	STDMETHOD(RemoveItem)(BSTR path);
};

OBJECT_ENTRY_AUTO(__uuidof(ProgramControlSetting), CProgramControlSetting)
