// Repair.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\Repair.h"
#include ".\RepairDlg.h"
#include <apputility.h>
#include <app_constants.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include <COM\FilterSetting_i.c>
#include <COM\FilterSetting.h>
#include <logger\logger.h>
#include <logger\loggerlevel.h>


#define INSTALLER_PARAMETER		TEXT("installer")
#define UNINSTALL_PARAMETER	TEXT("uninstaller")
#define SILENCE_PARAMETER	TEXT("silence")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairApp

BEGIN_MESSAGE_MAP(CRepairApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRepairApp 构造

CRepairApp::CRepairApp()
{
}


// 唯一的一个 CRepairApp 对象

CRepairApp theApp;


// CRepairApp 初始化
LONG setAppStatusForUninstaller() {
	// 设置状态， 如果
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// 获取应用程序状态
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			hr = pSetting->getApplicationStatus(&app_status);
			if (FAILED(hr)) {
				__LERR__("failed  on get state with HRESULT "<<hr);
			}
			pSetting->setApplicationStatus(SNOWMAN_STATUS_UNINSTALL);
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return app_status;
}
LONG setAppStatusForInstaller() {
	// 设置状态， 如果
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// 获取应用程序状态
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			hr = pSetting->getApplicationStatus(&app_status);
			if (FAILED(hr)) {
				__LERR__("failed  on get state with HRESULT "<<hr);
			}

			// 如果程序为卸载状态， 则设置为trial状态
			// 这一措施用于保证用户在安装程序的时候
			// 不需要覆盖设置， 就可以达到重新安装的目的
			// 但是这一行为必须保证用户能够正确获取状态信息
			// 不能是用户安装之后，从超期状态到注册状态

			if (app_status == SNOWMAN_STATUS_UNINSTALL) {
				pSetting->setApplicationStatus(SNOWMAN_STATUS_TRIAL);
			}
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return app_status;
}

LONG getAppStatus() {
	LONG status = SNOWMAN_STATUS_TRIAL;
	try {
		// 获取应用程序状态
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			pSetting->getApplicationStatus(&status);
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return status;
}

void Uninstall() {
	// 设置卸载状态
	LONG app_status = getAppStatus();	//SNOWMAN_STATUS_TRIAL;

	setAppStatusForUninstaller();	// 设置状态为卸载

	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.uninstall();
}

void Install() {
	// 设置应用程序状态
	// 确保其不会被卸载
	setAppStatusForInstaller();

	LONG app_status = getAppStatus();	//SNOWMAN_STATUS_TRIAL;
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair(true);

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		__LERR__("failed  on repair on reason that "<<errMsg);
		if (NULL == _tcsstr(GetCommandLine(), SILENCE_PARAMETER)) {
			AfxMessageBox(errMsg);
		}
		return;
	}


	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	if (NULL == _tcsstr(GetCommandLine(), SILENCE_PARAMETER)) {
		AfxMessageBox(strSucc);
	}

	__LTRC__("succeeded on repair.");
}

BOOL CRepairApp::InitInstance()
{
	init_debug_logger(".\\log\\dEyecare.log");
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(LOGGER_LEVEL);

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CoInitialize(NULL);

	// 如果是Installer调用， 则他会检测是否处于卸载状态
	// 如果是设为试用状态
	if (NULL != _tcsstr(GetCommandLine(), INSTALLER_PARAMETER)) {
		__LTRC__("installer call repair");
		Install();
	} else if (NULL != _tcsstr(GetCommandLine(), UNINSTALL_PARAMETER)) {
		__LTRC__("uninstaller call repair");
		Uninstall();
	} else {
		__LTRC__("user double click");
		Install();
	}

	return TRUE;
}
