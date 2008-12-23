// RulesSettings.h : CRulesSettings ������

#pragma once
#include "resource.h"       // ������
#include "RulesManagement.h"


// CRulesSettings

class ATL_NO_VTABLE CRulesSettings : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRulesSettings, &CLSID_RulesSettings>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRulesSettings, &IID_IRulesSettings, &LIBID_RulesManagementLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRulesSettings() {
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RULESSETTINGS)


BEGIN_COM_MAP(CRulesSettings)
	COM_INTERFACE_ENTRY(IRulesSettings)
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
	// ���ļ��ж�ȡ����
	STDMETHOD(initialize)(void);
	// ���ӹ����õ�DNS
	STDMETHOD(addFiltederDNS)(BSTR dns);
	STDMETHOD(enableIpCheck)(VARIANT_BOOL enable);
	STDMETHOD(removeFilteredDNS)(BSTR dns);
};

OBJECT_ENTRY_AUTO(__uuidof(RulesSettings), CRulesSettings)
