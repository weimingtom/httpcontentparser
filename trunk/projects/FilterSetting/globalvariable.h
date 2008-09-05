#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include <authorize.h>
#include <screensaver.h>
#include <eyecaresetting.h>
#include <webhistoryrecordersetting.h>
#include <dnssetting.h>

extern DNSSetting g_dnssetting;
extern DNSList g_black_dns_list;
extern DNSList g_white_dns_list;

extern Authorize g_authorize;
extern ScreenSaver g_screenSaver;
extern HINSTANCE g_hInstance;
extern EyecareSetting g_Eyecare_setting_;
extern WebHistoryRecorderSetting g_webhistoryRecordSetting_;

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__