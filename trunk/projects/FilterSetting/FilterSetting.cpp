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
#include <webhistoryrecordersetting.h>

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

// DNS Rules
DNSSetting g_dnssetting;
DNSList g_black_dns_list;
DNSList g_white_dns_list;


ScreenSaver g_screenSaver;			// 用于屏幕保存
Authorize g_authorize;				// 用于验证密码
EyecareSetting g_Eyecare_setting_;
HINSTANCE g_hInstance;
WebHistoryRecorderSetting g_webhistoryRecordSetting_;

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	g_hInstance = hInstance;

	g_dnssetting.initialize(&g_black_dns_list, &g_white_dns_list);

	// 还应该在上
	// TO DO
	g_Eyecare_setting_.initialize(&g_authorize, EyecareSetting::ENTERT_TIME);
	
	// 初始化屏幕记录
	g_screenSaver.initialize();

	 // 开启服务线程
	ServThread::getInstance();
	
	g_authorize.setNewPassword("123", PASSWORD_SU);
    return _AtlModule.WinMain(nShowCmd);
}

