// AppControl.h : CAppControl ������

#pragma once
#include "resource.h"       // ������

#include "FilterSetting.h"


// CAppControl

class ATL_NO_VTABLE CAppControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppControl, &CLSID_AppControl>,
	public IDispatchImpl<IAppControl, &IID_IAppControl, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAppControl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPCONTROL)


BEGIN_COM_MAP(CAppControl)
	COM_INTERFACE_ENTRY(IAppControl)
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
	STDMETHOD(RemoveItem)(BSTR path);
	STDMETHOD(GetFirstItem)(BSTR* path, LONG * hasValue);
	STDMETHOD(GetNextItem)(BSTR cur, BSTR* nxt, LONG *hasValue);
	STDMETHOD(checkApp)(BSTR fullpath, VARIANT_BOOL* result);
	STDMETHOD(isSettingEnabled)(VARIANT_BOOL* enabled);
	STDMETHOD(enable)(VARIANT_BOOL enabled);
};

OBJECT_ENTRY_AUTO(__uuidof(AppControl), CAppControl)
