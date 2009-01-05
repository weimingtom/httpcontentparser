#ifndef _FILTER_SETTING_GLOBALVARIABLE_H__
#define _FILTER_SETTING_GLOBALVARIABLE_H__

#include "FilterSetting.h"
#include ".\registerinfo.h"
#include <authorize.h>
#include <eyecaresetting.h>
#include <webhistoryrecordersetting.h>
#include <dnssetting.h>
#include <xmlconfiguration.h>



// extern Authorize g_authorize;
extern XMLConfiguration g_configuration;
extern HINSTANCE g_hInstance;
extern RegisterInfo g_registerInfo;

#endif  // _FILTER_SETTING_GLOBALVARIABLE_H__