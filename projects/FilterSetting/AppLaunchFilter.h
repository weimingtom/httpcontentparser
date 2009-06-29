// AppLaunchFilter.h : CAppLaunchFilter µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "FilterSetting.h"
#include <comdef.h>
#include <shlobj.h>
#include <shlguid.h>

#ifndef _VISUAL_STUDIO_2008_
struct __declspec(uuid("000214FB-0000-0000-C000-000000000046")) IShellExecuteHook; 
#endif

// CAppLaunchFilter

class ATL_NO_VTABLE CAppLaunchFilter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppLaunchFilter, &CLSID_AppLaunchFilter>,
	public IAppLaunchFilter,
	public IShellExecuteHook
{
public:
	CAppLaunchFilter()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPLAUNCHFILTER)


BEGIN_COM_MAP(CAppLaunchFilter)
	COM_INTERFACE_ENTRY(IAppLaunchFilter)
	COM_INTERFACE_ENTRY(IShellExecuteHook)
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
	STDMETHOD (Execute)(LPSHELLEXECUTEINFO  pei);
};

OBJECT_ENTRY_AUTO(__uuidof(AppLaunchFilter), CAppLaunchFilter)
