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


#ifdef _DEBUG

#	pragma comment(lib, "settingd.lib")
#else 
#	pragma comment(lib, "setting.lib")
#endif


#pragma comment(lib, "ws2_32.lib")

#endif  // _SETTING_STDAFX_H__