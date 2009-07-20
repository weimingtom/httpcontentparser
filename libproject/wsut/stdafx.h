// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <windows.h>
#include <tchar.h>

#ifdef _DEBUG
#pragma comment(lib, "apputilityMTd.lib")
#else
#pragma comment(lib, "apputilityMT.lib")
#endif