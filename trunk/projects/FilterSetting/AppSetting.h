// AppSetting.h : CAppSetting ������

#pragma once
#include "resource.h"       // ������

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
	// �ȼ�
	STDMETHOD(setHotkey)(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess);

	// ģʽ�л�
	STDMETHOD(switchModel)(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc);
	STDMETHOD(get_ParentModel)(VARIANT_BOOL* pVal);

	// ע�����Ƿ��Ѿ�ע��
	STDMETHOD(Registered)(VARIANT_BOOL* registeded);
	STDMETHOD(Register)(BSTR bstr, VARIANT_BOOL* bSucc);

	// ·������
	STDMETHOD(GetInstallPath)(BSTR* path);	// ��ȡ��װ·��
	STDMETHOD(getImageFolder)(BSTR* path);
	STDMETHOD(getPagesFolder)(BSTR* path);

	// ��ʱ�Զ��л�ģʽ
	// ��ʱ������
	STDMETHOD(setTimeoutValue)(LONG seconds);
	STDMETHOD(get_TimeoutSwitchEnabled)(VARIANT_BOOL* pVal);
	STDMETHOD(put_TimeoutSwitchEnabled)(VARIANT_BOOL newVal);
	STDMETHOD(get_LefttimeToSwitch)(LONG* pVal);
	STDMETHOD(getHotkey)(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier);
};

OBJECT_ENTRY_AUTO(__uuidof(AppSetting), CAppSetting)
