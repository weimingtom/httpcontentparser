// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <conio.h>
#include <process.h>
#include <assert.h>
#include <winsock2.h>

#include <vector>
#include <map>
#include <set>
#include <string>
#include <aclapi.h>

#pragma comment(lib, "strsafe.lib")
#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "utility.lib")
#endif
