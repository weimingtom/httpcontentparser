// ScreenSave.h : CScreenSave µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ
#include "FilterSetting.h"
#include "globalvariable.h"

// CScreenSave

class ATL_NO_VTABLE CScreenSave : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScreenSave, &CLSID_ScreenSave>,
	public ISupportErrorInfo,
	public IDispatchImpl<IScreenSave, &IID_IScreenSave, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CScreenSave()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCREENSAVE)


BEGIN_COM_MAP(CScreenSave)
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
	STDMETHOD(isEnabled)(VARIANT_BOOL* enabled);
	STDMETHOD(ClearCache)(void);
	STDMETHOD(setAutoClearTimespan)(LONG seconds);
};

OBJECT_ENTRY_AUTO(__uuidof(ScreenSave), CScreenSave)
