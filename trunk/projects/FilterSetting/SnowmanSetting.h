// SnowmanSetting.h : CSnowmanSetting ������

#pragma once
#include "resource.h"       // ������

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
	// �ȼ�
	STDMETHOD(getHotkey)(LONG type, USHORT* wVirtualKeyCode, USHORT* wModifier);
	STDMETHOD(setHotkey)(USHORT wVirtualKeyCode, USHORT wModifiers, LONG type, VARIANT_BOOL* bSuccess);

	// ģʽ�л�
	STDMETHOD(switchModel)(VARIANT_BOOL bParent, BSTR pwd, VARIANT_BOOL* bSucc);
	STDMETHOD(get_ParentModel)(VARIANT_BOOL* pVal);


	// ·������
	STDMETHOD(GetInstallPath)(BSTR* path);	// ��ȡ��װ·��
	STDMETHOD(getImageFolder)(BSTR* path);
	STDMETHOD(getPagesFolder)(BSTR* path);

	// ��ʱ�Զ��л�ģʽ
	STDMETHOD(get_autoSwitchOnClose)(VARIANT_BOOL* pVal);
	STDMETHOD(put_autoSwitchOnClose)(VARIANT_BOOL newVal);
	STDMETHOD(get_askMeAgain)(VARIANT_BOOL* pVal);
	STDMETHOD(put_askMeAgain)(VARIANT_BOOL newVal);

		// ��ʱ������
	STDMETHOD(setTimeoutValue)(LONG seconds);
	STDMETHOD(get_TimeoutSwitchEnabled)(VARIANT_BOOL* pVal);
	STDMETHOD(put_TimeoutSwitchEnabled)(VARIANT_BOOL newVal);
	STDMETHOD(get_LefttimeToSwitch)(LONG* pVal);

	// ��ȡӦ�ó���״̬
	STDMETHOD(getApplicationStatus)(LONG* status);
};

OBJECT_ENTRY_AUTO(__uuidof(SnowmanSetting), CSnowmanSetting)
