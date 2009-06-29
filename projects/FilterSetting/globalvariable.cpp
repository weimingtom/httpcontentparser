#include "stdafx.h"
#include ".\globalvariable.h"
#include <softwareStatus.h>
#include <logger/logger.h>
#include <DebugOutput.h>
#include <apputility.h>

// extern Authorize g_authorize;
XMLConfiguration g_configuration;
HINSTANCE g_hInstance;
SeachKeywordUtil g_searchwordUtil;
WebsitesUtil g_websitesUtil;

namespace {
software_encrypt::LicenseInfo g_licenseInfo;
bool checkInSameDirectory(LPCTSTR lpstr) ;
};

bool checkApppath(const TCHAR *fullpath) {
	// 如果是在本目录下的文件永远都能够运行
	if (true == checkInSameDirectory(fullpath)) {
		_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Check Item :  "<< (TCHAR*)_bstr_t(fullpath)<<" In the same path with ext");
		return true;
	} else {
		bool result =  g_configuration.getProgramControl()->check((TCHAR*)_bstr_t(fullpath));

		__LTRC__((result? "pass " : "block ")<<"app check "<< (char*)_bstr_t(fullpath));
		_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Check Item :  "
			<< (TCHAR*)_bstr_t(fullpath)
			<< "  result : "<<(result ? "passed" : "blocked"));
		return result;
	}
}

int getAppStatus() {
	if ( true == g_configuration.uninstall()) {
		return SNOWMAN_STATUS_UNINSTALL;
	} else {
		return  g_licenseInfo.getAppStatus();
	}
}

int refreshAppstatus() {
	g_licenseInfo.initialize();
	SettingItem::setAppStatus(getAppStatus());
	return 0;
}

int getInstallDays() {
	return g_licenseInfo.getInstallDays();
}

bool tryRegister(const char *sn) {
	return g_licenseInfo.regApp(sn);
}

bool registered() {
	return g_licenseInfo.registered();
}

namespace {
bool checkInSameDirectory(LPCTSTR lpstr) {
	TCHAR exefiledir[MAX_PATH]; 
	GetFileNameDir(lpstr, exefiledir, MAX_PATH);
	
	// 获取本文件的路径
	TCHAR myselfdir[MAX_PATH], myfilepath[MAX_PATH];
	GetModuleFileName(NULL, myfilepath, MAX_PATH);
	GetFileNameDir(myfilepath, myselfdir, MAX_PATH);

	if (_tcsstr(myselfdir, exefiledir) != NULL) {
		return true;
	} else {
		return false;
	}
}
};