// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#ifndef _SETTING_STDAFX_H__
#define _SETTING_STDAFX_H__


#include <iostream>
#include <tchar.h>

#include <objbase.h>
#include <windows.h>
#include <comdef.h>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")

#ifdef _DEBUG
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "utility.lib")
#endif

#endif  // _SETTING_STDAFX_H__