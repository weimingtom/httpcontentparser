// RulesChecker.h : CRulesChecker µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "RulesHolder.h"


// CRulesChecker

class ATL_NO_VTABLE CRulesChecker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRulesChecker, &CLSID_RulesChecker>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRulesChecker, &IID_IRulesChecker, &LIBID_RulesHolderLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRulesChecker()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RULESCHECKER)


BEGIN_COM_MAP(CRulesChecker)
	COM_INTERFACE_ENTRY(IRulesChecker)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

public:
	STDMETHOD(checkIp)(ULONG ip, VARIANT_BOOL* bFiltered);
};

OBJECT_ENTRY_AUTO(__uuidof(RulesChecker), CRulesChecker)
