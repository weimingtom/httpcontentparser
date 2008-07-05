// RulesManagement.cpp : DLL ������ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "RulesManagement.h"
#include ".\globaldata.h"

CGlobalData g_globalData;
extern LONG	g_share_nProcessCount;

class CRulesManagementModule : public CAtlDllModuleT< CRulesManagementModule >
{
public :
	DECLARE_LIBID(LIBID_RulesManagementLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RULESMANAGEMENT, "{BC26849D-420C-4CBF-BF6A-2110C1B38FB8}")
};

CRulesManagementModule _AtlModule;


// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	if (dwReason == DLL_PROCESS_ATTACH) {
		InterlockedIncrement(&g_share_nProcessCount);
		g_globalData.loadSetting();

	} else if (dwReason == DLL_PROCESS_DETACH) {
		
		InterlockedDecrement(&g_share_nProcessCount);
		g_globalData.storeSetting();
	}
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
