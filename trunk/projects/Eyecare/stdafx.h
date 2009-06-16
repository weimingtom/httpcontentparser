// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define		WINVER 0x0400
#define    _WIN32_WINNT 0x0400

// Windows 头文件:
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include   <commctrl.h>

#ifdef _DEBUG
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "winlockd.lib")
#pragma comment(lib, "loggerd.lib")
#else
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "winlock.lib")
#pragma comment(lib, "logger.lib")
#endif
