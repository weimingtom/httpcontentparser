// AppRegInfo.h : CAppRegInfo 的声明

#pragma once
#include "resource.h"       // 主符号

#include "FilterSetting.h"


// CAppRegInfo

class ATL_NO_VTABLE CAppRegInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppRegInfo, &CLSID_AppRegInfo>,
	public IDispatchImpl<IAppRegInfo, &IID_IAppRegInfo, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAppRegInfo()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_APPREGINFO)


BEGIN_COM_MAP(CAppRegInfo)
	COM_INTERFACE_ENTRY(IAppRegInfo)
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
	// 注册于是否已经注册
	STDMETHOD(Registered)(VARIANT_BOOL* registeded);
	STDMETHOD(Register)(BSTR bstr, VARIANT_BOOL* bSucc);
	
	STDMETHOD(get_InstallDays)(LONG* pVal);
	STDMETHOD(get_LeftDays)(LONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(AppRegInfo), CAppRegInfo)
