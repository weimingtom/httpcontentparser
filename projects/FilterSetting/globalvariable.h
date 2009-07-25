#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include <setting\authorize.h>
#include <setting\eyecaresetting.h>
#include <setting\webhistoryrecordersetting.h>
#include <setting\dnssetting.h>
#include <setting\xmlconfiguration.h>
#include <searchkeywordutil.h>
#include <websitesutil.h>
#include <softwareEncrypt\LicenseInfo.h>

// extern Authorize g_authorize;
extern XMLConfiguration g_configuration;
extern HINSTANCE g_hInstance;
extern  SeachKeywordUtil g_searchwordUtil;
extern WebsitesUtil g_websitesUtil;


LONG getAppStatus();
LONG refreshAppstatus();
LONG getInstallDays();
bool registered();
bool tryRegister(const char * sn);
bool checkApppath(const TCHAR *fullpath);

// 显示通知消息
void NotifyUser(const char * msg);

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__