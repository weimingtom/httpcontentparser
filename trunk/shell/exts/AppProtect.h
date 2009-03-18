// AppProtect.h : CAppProtect µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ
#include "Exts.h"
#include <comdef.h>
#include <shlobj.h>
#include <shlguid.h>
#include <shobjidl.h>

#ifndef _VISUAL_STUDIO_2008_
struct __declspec(uuid("000214FC-0000-0000-C000-000000000046")) ICopyHook; 
#endif 

// CAppProtect

class ATL_NO_VTABLE CAppProtect : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppProtect, &CLSID_AppProtect>,
	public IAppProtect,
	public ICopyHook
{
public:
	CAppProtect()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPPROTECT)


BEGIN_COM_MAP(CAppProtect)
	COM_INTERFACE_ENTRY(IAppProtect)
	COM_INTERFACE_ENTRY(ICopyHook)
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
	// interface ICopyHook
	UINT __stdcall CopyCallback(HWND hwnd, UINT wFunc, UINT wFlags,
		LPCTSTR pszSrcFile,  DWORD dwSrcAttribs, LPCTSTR pszDestFile, DWORD dwDestAttribs);
};

OBJECT_ENTRY_AUTO(__uuidof(AppProtect), CAppProtect)
