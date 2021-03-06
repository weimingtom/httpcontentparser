// SearchRule.h : CSearchRule ������

#pragma once
#include ".\resource.h"       // ������
#include ".\FilterSetting.h"


// CSearchRule

class ATL_NO_VTABLE CSearchRule : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSearchRule, &CLSID_SearchRule>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISearchRule, &IID_ISearchRule, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSearchRule()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SEARCHRULE)


BEGIN_COM_MAP(CSearchRule)
	COM_INTERFACE_ENTRY(ISearchRule)
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

	STDMETHOD(check)(BSTR search_word, BSTR host_name, VARIANT_BOOL* pass);
	STDMETHOD(addBlackSeachword)(BSTR searchword);
	STDMETHOD(enableCheckSeachEngine)(BSTR searchengine, VARIANT_BOOL enabled);
	STDMETHOD(removeBlackSeachWord)(BSTR blackword);
	STDMETHOD(isSettingEnabled)(BSTR searchengine, VARIANT_BOOL* isSettingenabled);
	STDMETHOD(getFirstSearchWord)(BSTR* first);
	STDMETHOD(getNextSearchWord)(BSTR cur, BSTR* next);
};

OBJECT_ENTRY_AUTO(__uuidof(SearchRule), CSearchRule)
