// ScreenSave.h : CScreenshotRecord ������

#pragma once
#include "resource.h"       // ������
#include "FilterSetting.h"
#include "globalvariable.h"

// CScreenshotRecord

class ATL_NO_VTABLE CScreenshotRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScreenshotRecord, &CLSID_ScreenSave>,
	public ISupportErrorInfo,
	public IDispatchImpl<IScreenSave, &IID_IScreenSave, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CScreenshotRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCREENSAVE)


BEGIN_COM_MAP(CScreenshotRecord)
	COM_INTERFACE_ENTRY(IScreenSave)
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
	STDMETHOD(enableScreenSave)(VARIANT_BOOL enabled);
	STDMETHOD(setTimeSpan)(LONG seconds);
	STDMETHOD(getTimeSpan)(LONG* secs);
	STDMETHOD(isEnabled)(VARIANT_BOOL* enabled);
	STDMETHOD(ClearCache)(void);
	

	STDMETHOD(setAutoClearTimespan)(LONG days);
	STDMETHOD(getAutoClearSpan)(LONG* days);
	STDMETHOD(get_AutocleanEnabled)(VARIANT_BOOL* pVal);
	STDMETHOD(put_AutocleanEnabled)(VARIANT_BOOL newVal);
	
	STDMETHOD(isSettingEnabled)(VARIANT_BOOL* enabled);
	STDMETHOD(enableAutoClear)(VARIANT_BOOL enabled);
	STDMETHOD(isAutoClearEnabled)(VARIANT_BOOL* enabled);
	
};

OBJECT_ENTRY_AUTO(__uuidof(ScreenSave), CScreenshotRecord)
