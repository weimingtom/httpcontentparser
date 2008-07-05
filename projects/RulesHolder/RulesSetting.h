// RulesSetting.h : CRulesSetting ������

#pragma once
#include "resource.h"       // ������

#include "RulesHolder.h"


// CRulesSetting

class ATL_NO_VTABLE CRulesSetting : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRulesSetting, &CLSID_RulesSetting>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRulesSetting, &IID_IRulesSetting, &LIBID_RulesHolderLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRulesSetting()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RULESSETTING)


BEGIN_COM_MAP(CRulesSetting)
	COM_INTERFACE_ENTRY(IRulesSetting)
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
	// ���ļ��ж�ȡ����
	STDMETHOD(initialize)(void);
	// ���ӹ����õ�DNS
	STDMETHOD(addFiltederDNS)(BSTR dns);
	STDMETHOD(enableIpCheck)(VARIANT_BOOL enable);
	STDMETHOD(removeFilteredDNS)(BSTR dns);
};

OBJECT_ENTRY_AUTO(__uuidof(RulesSetting), CRulesSetting)
