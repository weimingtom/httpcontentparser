#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include <authorize.h>
#include <eyecaresetting.h>
#include <webhistoryrecordersetting.h>
#include <dnssetting.h>
#include <xmlconfiguration.h>
#include <searchkeywordutil.h>
#include <websitesutil.h>
#include <softwareEncrypt\LicenseInfo.h>

// extern Authorize g_authorize;
extern XMLConfiguration g_configuration;
extern HINSTANCE g_hInstance;
extern  SeachKeywordUtil g_searchwordUtil;
extern WebsitesUtil g_websitesUtil;
extern software_encrypt::LicenseInfo g_licenseInfo;

int getAppStatus();
int refreshAppstatus();

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__