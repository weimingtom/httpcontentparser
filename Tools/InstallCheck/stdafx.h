// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <windows.h>

#include <apputility.h>
#include <AppInstallValidate.h>


#ifndef DEBUG
#pragma comment(lib, "Apputility.lib")
#else
#pragma comment(lib, "Apputilityd.lib")
#endif