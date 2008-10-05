// Eyecare.h : CEyecare 的声明

#pragma once
#include "resource.h"       // 主符号
#include "FilterSetting.h"

#include <eyecaresetting.h>

// CEyecare

class ATL_NO_VTABLE CEyecare : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEyecare, &CLSID_Eyecare>,
	public ISupportErrorInfo,
	public IDispatchImpl<IEyecare, &IID_IEyecare, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEyecare();
DECLARE_REGISTRY_RESOURCEID(IDR_EYECARE)


BEGIN_COM_MAP(CEyecare)
	COM_INTERFACE_ENTRY(IEyecare)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(setPassword)(BSTR password);			// 设置密码， 如果设置空密码， 则为使用系统管理员密码
	STDMETHOD(setEyecareTime)(LONG mintues);			// 设置休息时间的长度
	STDMETHOD(setEnterTime)(LONG mintues);	// 设置娱乐事件的长度
	STDMETHOD(getEyecareTime)(LONG* mintues);			// 获取休息时间的长度
	STDMETHOD(getEnterTime)(LONG* second);	// 获取娱乐事件的长度
	STDMETHOD(getTimeLeft)(LONG* second);			// 状态切换的剩余时间
	STDMETHOD(getState)(LONG* state);				// 获取状态
	STDMETHOD(swithToEntertainment)(BSTR password, VARIANT_BOOL *bSuccess); // 切换到娱乐状体
	STDMETHOD(trySwitch)(LONG* state);
	STDMETHOD(LockScreen)(void);
	STDMETHOD(setTermMode)(LONG mode);
	STDMETHOD(getTermMode)(LONG* mode);
};

OBJECT_ENTRY_AUTO(__uuidof(Eyecare), CEyecare)
