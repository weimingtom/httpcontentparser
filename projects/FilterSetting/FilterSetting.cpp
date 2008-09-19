// FilterSetting.cpp : WinMain ��ʵ��

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
#include <xmlconfiguration.h>

class CFilterSettingModule : public CAtlServiceModuleT< CFilterSettingModule, IDS_SERVICENAME >
{
public :
	DECLARE_LIBID(LIBID_FilterSettingLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILTERSETTING, "{92277243-F9BC-4ED8-9DD1-06D31FB572CF}")
	HRESULT InitializeSecurity() throw()
	{
		// TODO : ���� CoInitializeSecurity ��Ϊ�����ṩ�ʵ��� 
		// ��ȫ����
		// ���� - PKT ����������֤��
		// RPC_C_IMP_LEVEL_IDENTIFY ��ģ�⼶��
		// �Լ��ʵ��ķǿհ�ȫ˵������

		return S_OK;
	}
};

CFilterSettingModule _AtlModule;

// DNS Rules
DNSSetting g_dnssetting;

XMLConfiguration g_configuration;

ScreenSaver g_screenSaver;			// ������Ļ����
HINSTANCE g_hInstance;


extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	g_hInstance = hInstance;
	g_configuration.setInstance(hInstance);
	g_dnssetting.initialize(g_configuration.getBlackURLSet(), g_configuration.getWhiteURLSet());
	
	// ��ʼ����Ļ��¼
	g_screenSaver.initialize();

	 // ���������߳�
	ServThread::getInstance();
	
    return _AtlModule.WinMain(nShowCmd);
}

