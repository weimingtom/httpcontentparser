// WebContentRecord.h : CWebContentRecord ������

#pragma once
#include "resource.h"       // ������

#include "FilterSetting.h"


// CWebContentRecord
// ��¼��վ�������ȵ���������
class ATL_NO_VTABLE CWebContentRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebContentRecord, &CLSID_WebContentRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IWebContentRecord, &IID_IWebContentRecord, &LIBID_FilterSettingLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWebContentRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WEBCONTENTRECORD)


BEGIN_COM_MAP(CWebContentRecord)
	COM_INTERFACE_ENTRY(IWebContentRecord)
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
	// ���ڴ��������ؼ���
	STDMETHOD(SearchKeyword)(BSTR keyword, LONG searchEngine);
	STDMETHOD(GetFirstSearchKeyword)(BSTR* keyword, LONG* times, LONG* searchEngine, LONG* timeHighPart, LONG* timeLowPart);
	STDMETHOD(GetNextSearchKeyword)(BSTR cur, BSTR* next, LONG* times, LONG* searchEngine, LONG* timeHighPart, LONG* timeLowPart);

	// ������վ
	STDMETHOD(GetFirstWebsite)(BSTR* NAME, LONG* times, LONG* high, LONG* low);
	STDMETHOD(GetNextWebSite)(BSTR cur, BSTR* next, LONG* times, LONG* hight, LONG* low);
};

OBJECT_ENTRY_AUTO(__uuidof(WebContentRecord), CWebContentRecord)
