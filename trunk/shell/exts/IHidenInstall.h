// IHidenInstall.h : CIHidenInstall µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "exts.h"


// CIHidenInstall

class ATL_NO_VTABLE CIHidenInstall : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIHidenInstall, &CLSID_IHidenInstall>,
	public IIHidenInstall
{
public:
	CIHidenInstall()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IHIDENINSTALL)


BEGIN_COM_MAP(CIHidenInstall)
	COM_INTERFACE_ENTRY(IIHidenInstall)
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

};

OBJECT_ENTRY_AUTO(__uuidof(IHidenInstall), CIHidenInstall)
