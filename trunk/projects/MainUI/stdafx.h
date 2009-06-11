// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件

#pragma once				


#define _CRT_SECURE_NO_DEPRECATE

#ifdef _VISUAL_STUDIO_2008_
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#endif

#include <afx.h>
#include <afxcmn.h>
#include <afxcview.h>
#include <afxdlgs.h>
#include <afxdisp.h>
#include <afxtempl.h>
#include <afxmt.h>
#include <shlwapi.h>
#include <SnowmanErrno.h>

#ifdef _VISUAL_STUDIO_2008_
       #include <tmschema.h>
#else
    #if _MSC_VER >= 1500
         #include <vsstyle.h>
         
    #endif
#endif


#ifdef _DEBUG
#pragma comment(lib, "apputilityd.lib")
#else
#pragma comment(lib, "apputility.lib")
#endif 


#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

#pragma comment(lib, "log4cxx.lib")
#pragma comment(lib, "uxtheme.lib")

#include "Gdiplus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#include "resource.h"
#include <afxwin.h>


