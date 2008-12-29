// RulesChecker.h : CRulesChecker µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ
#include "RulesManagement.h"


// CRulesChecker

class ATL_NO_VTABLE CRulesChecker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRulesChecker, &CLSID_RulesChecker>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRulesChecker, &IID_IRulesChecker, &LIBID_RulesManagementLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRulesChecker() {
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RULESCHECKER)


BEGIN_COM_MAP(CRulesChecker)
	COM_INTERFACE_ENTRY(IRulesChecker)
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

OBJECT_ENTRY_AUTO(__uuidof(RulesChecker), CRulesChecker)
