// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#ifndef _TEST_SELECTIO_STDAFX_H__
#define _TEST_SELECTIO_STDAFX_H__

#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

#include "..\..\projects\PacketsGrasper\SelectIO.h"

#ifdef _DEBUG
#	pragma comment(lib, ".\\SelectIODebug\\selectiod.lib")
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "apputilityd.lib")
#else 
#	pragma comment(lib, ".\\selectiorelease\\selectio.lib")
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "apputility.lib")
#endif

#endif  // _TEST_SELECTIO_STDAFX_H__