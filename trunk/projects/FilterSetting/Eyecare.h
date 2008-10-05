// Eyecare.h : CEyecare ������

#pragma once
#include "resource.h"       // ������
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
	STDMETHOD(setPassword)(BSTR password);			// �������룬 ������ÿ����룬 ��Ϊʹ��ϵͳ����Ա����
	STDMETHOD(setEyecareTime)(LONG mintues);			// ������Ϣʱ��ĳ���
	STDMETHOD(setEnterTime)(LONG mintues);	// ���������¼��ĳ���
	STDMETHOD(getEyecareTime)(LONG* mintues);			// ��ȡ��Ϣʱ��ĳ���
	STDMETHOD(getEnterTime)(LONG* second);	// ��ȡ�����¼��ĳ���
	STDMETHOD(getTimeLeft)(LONG* second);			// ״̬�л���ʣ��ʱ��
	STDMETHOD(getState)(LONG* state);				// ��ȡ״̬
	STDMETHOD(swithToEntertainment)(BSTR password, VARIANT_BOOL *bSuccess); // �л�������״��
	STDMETHOD(trySwitch)(LONG* state);
	STDMETHOD(LockScreen)(void);
	STDMETHOD(setTermMode)(LONG mode);
	STDMETHOD(getTermMode)(LONG* mode);
};

OBJECT_ENTRY_AUTO(__uuidof(Eyecare), CEyecare)
