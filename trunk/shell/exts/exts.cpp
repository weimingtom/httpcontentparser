// exts.cpp : DLL ������ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "exts.h"

HINSTANCE g_hInstance;

class CextsModule : public CAtlDllModuleT< CextsModule >
{
public :
	DECLARE_LIBID(LIBID_extsLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_EXTS, "{385E71CC-E9FB-401D-9D17-17DC41E8C770}")
};

CextsModule _AtlModule;


// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	g_hInstance = hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// ����ȷ�� DLL �Ƿ���� OLE ж��
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// ����һ���๤���Դ������������͵Ķ���
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - ������ӵ�ϵͳע���
STDAPI DllRegisterServer(void)
{
    // ע��������Ϳ�����Ϳ��е����нӿ�
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
