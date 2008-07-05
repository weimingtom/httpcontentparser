// ExeRulesSetting.h : CExeRulesSetting 的声明

#pragma once
#include "resource.h"       // 主符号

#include "Rules_management_exe.h"


// CExeRulesSetting

class ATL_NO_VTABLE CExeRulesSetting : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExeRulesSetting, &CLSID_ExeRulesSetting>,
	public IDispatchImpl<IExeRulesSetting, &IID_IExeRulesSetting, &LIBID_Rules_management_exeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExeRulesSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXERULESSETTING)


BEGIN_COM_MAP(CExeRulesSetting)
	COM_INTERFACE_ENTRY(IExeRulesSetting)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() {
		return S_OK;
	}
	
	void FinalRelease() {
	}

public:
	// 从文件中读取规则
	STDMETHOD(initialize)(void);
	// 增加过滤用的DNS
	STDMETHOD(addFiltederDNS)(BSTR dns);
	STDMETHOD(enableIpCheck)(VARIANT_BOOL enable);
	STDMETHOD(removeFilteredDNS)(BSTR dns);
};

OBJECT_ENTRY_AUTO(__uuidof(ExeRulesSetting), CExeRulesSetting)
