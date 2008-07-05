// ExeRulesChecker.h : CExeRulesChecker µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "Rules_management_exe.h"


// CExeRulesChecker

class ATL_NO_VTABLE CExeRulesChecker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExeRulesChecker, &CLSID_ExeRulesChecker>,
	public ISupportErrorInfo,
	public IDispatchImpl<IExeRulesChecker, &IID_IExeRulesChecker, &LIBID_Rules_management_exeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeRulesChecker()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXERULESCHECKER)


BEGIN_COM_MAP(CExeRulesChecker)
	COM_INTERFACE_ENTRY(IExeRulesChecker)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() {
		return S_OK;
	}
	
	void FinalRelease()  {
	}

public:
	STDMETHOD(checkIp)(ULONG ip, VARIANT_BOOL* bFiltered);
};

OBJECT_ENTRY_AUTO(__uuidof(ExeRulesChecker), CExeRulesChecker)
