#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include <authorize.h>
#include <screensaver.h>
#include <eyecaresetting.h>
#include <webhistoryrecordersetting.h>

extern GlobalSetting global_setting_;
extern Authorize g_authorize;
extern ScreenSaver g_screenSaver;
extern HINSTANCE g_hInstance;
extern EyecareSetting g_Eyecare_setting_;
extern WebHistoryRecorderSetting g_webhistoryRecordSetting_;

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__