// RulesManagement.cpp : DLL 导出的实现。

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


// DLL 入口点
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


// 用于确定 DLL 是否可由 OLE 卸载
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// 返回一个类工厂以创建所请求类型的对象
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - 将项添加到系统注册表
STDAPI DllRegisterServer(void)
{
    // 注册对象、类型库和类型库中的所有接口
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - 将项从系统注册表中移除
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
