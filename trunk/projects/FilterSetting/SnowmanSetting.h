// SnowmanSetting.h : CSnowmanSetting 的声明

#pragma once
#include "resource.h"       // 主符号

#include "FilterSetting.h"


// CSnowmanSetting

class ATL_NO_VTABLE CSnowmanSetting : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSnowmanSetting, &CLSID_SnowmanSetting>,
	public IDispatchImpl<ISnowmanSetting, &IID_ISnowmanSetting, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSnowmanSetting()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SNOWMANSETTING)


BEGIN_COM_MAP(CSnowmanSetting)
	COM_INTERFACE_ENTRY(ISnowmanSetting)
	COM_INTERFACE_ENTRY(IDispatch)
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
	// 热键
	STDMETHOD(getHotkey)(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier);
	STDMETHOD(setHotkey)(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess);

	// 模式切换
	STDMETHOD(switchModel)(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc);
	STDMETHOD(get_ParentModel)(VARIANT_BOOL* pVal);


	// 路径设置
	STDMETHOD(GetInstallPath)(BSTR* path);	// 获取安装路径
	STDMETHOD(getImageFolder)(BSTR* path);
	STDMETHOD(getPagesFolder)(BSTR* path);

	// 超时自动切换模式
	STDMETHOD(get_autoSwitchOnClose)(VARIANT_BOOL* pVal);
	STDMETHOD(put_autoSwitchOnClose)(VARIANT_BOOL newVal);
	STDMETHOD(get_askMeAgain)(VARIANT_BOOL* pVal);
	STDMETHOD(put_askMeAgain)(VARIANT_BOOL newVal);

		// 暂时被废弃
	STDMETHOD(setTimeoutValue)(LONG seconds);
	STDMETHOD(get_TimeoutSwitchEnabled)(VARIANT_BOOL* pVal);
	STDMETHOD(put_TimeoutSwitchEnabled)(VARIANT_BOOL newVal);
	STDMETHOD(get_LefttimeToSwitch)(LONG* pVal);

	// 获取应用程序状态
	STDMETHOD(getApplicationStatus)(LONG* status);
};

OBJECT_ENTRY_AUTO(__uuidof(SnowmanSetting), CSnowmanSetting)
