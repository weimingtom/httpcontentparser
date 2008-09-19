#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include <authorize.h>
#include <screensaver.h>
#include <eyecaresetting.h>
#include <webhistoryrecordersetting.h>
#include <dnssetting.h>
#include <xmlconfiguration.h>

extern DNSSetting g_dnssetting;


// extern Authorize g_authorize;
extern XMLConfiguration g_configuration;
extern ScreenSaver g_screenSaver;
extern HINSTANCE g_hInstance;

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__