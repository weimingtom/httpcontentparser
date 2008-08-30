// FilterSetting.cpp : WinMain 的实现

#include "stdafx.h"
#include "resource.h"
#include "globalvariable.h"
#include "FilterSetting.h"
#include ".\servthread.h"
#include "sysutility.h"
#include <passwordtype.h>
#include <string>
#include <screensaver.h>

class CFilterSettingModule : public CAtlServiceModuleT< CFilterSettingModule, IDS_SERVICENAME >
{
public :
	DECLARE_LIBID(LIBID_FilterSettingLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILTERSETTING, "{92277243-F9BC-4ED8-9DD1-06D31FB572CF}")
	HRESULT InitializeSecurity() throw()
	{
		// TODO : 调用 CoInitializeSecurity 并为服务提供适当的 
		// 安全设置
		// 建议 - PKT 级别的身份验证、
		// RPC_C_IMP_LEVEL_IDENTIFY 的模拟级别
		// 以及适当的非空安全说明符。

		return S_OK;
	}
};

CFilterSettingModule _AtlModule;
ScreenSaver g_screenSaver;
Authorize g_authorize;
GlobalSetting global_setting_;
EyecareSetting g_Eyecare_setting_;
HINSTANCE g_hInstance;

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{

	SaveScreen(hInstance);
	g_Eyecare_setting_.initialize(&g_authorize);
	g_hInstance = hInstance;
	g_screenSaver.initialize();
	global_setting_.initialize();
	ServThread::getInstance(); // 开启服务线程

	g_authorize.setNewPassword("123", PASSWORD_SU);
    return _AtlModule.WinMain(nShowCmd);
}

