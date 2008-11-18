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
#	pragma comment(lib, "sysutilityd.lib")
#	pragma comment(lib, "syshookd.lib")
#else
#	pragma comment(lib, "sysutility.lib")
#	pragma comment(lib, "syshook.lib")
#endif
