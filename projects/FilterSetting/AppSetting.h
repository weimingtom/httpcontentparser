// AppSetting.h : CAppSetting 的声明

#pragma once
#include "resource.h"       // 主符号

#include "FilterSetting.h"


// CAppSetting

class ATL_NO_VTABLE CAppSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppSetting, &CLSID_AppSetting>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAppSetting, &IID_IAppSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAppSetting() {
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPSETTING)


BEGIN_COM_MAP(CAppSetting)
	COM_INTERFACE_ENTRY(IAppSetting)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() {
		return S_OK;
	}
	
	void FinalRelease() {
	}

public:
	// 热键
	STDMETHOD(setHotkey)(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess);

	// 模式切换
	STDMETHOD(switchModel)(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc);
	STDMETHOD(get_ParentModel)(VARIANT_BOOL* pVal);

	// 注册于是否已经注册
	STDMETHOD(Registered)(VARIANT_BOOL* registeded);
	STDMETHOD(Register)(BSTR bstr, VARIANT_BOOL* bSucc);

	// 路径设置
	STDMETHOD(GetInstallPath)(BSTR* path);	// 获取安装路径
	STDMETHOD(getImageFolder)(BSTR* path);
	STDMETHOD(getPagesFolder)(BSTR* path);

	// 超时自动切换模式
	// 暂时被废弃
	STDMETHOD(setTimeoutValue)(LONG seconds);
	STDMETHOD(get_TimeoutSwitchEnabled)(VARIANT_BOOL* pVal);
	STDMETHOD(put_TimeoutSwitchEnabled)(VARIANT_BOOL newVal);
	STDMETHOD(get_LefttimeToSwitch)(LONG* pVal);
	STDMETHOD(getHotkey)(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier);
};

OBJECT_ENTRY_AUTO(__uuidof(AppSetting), CAppSetting)
