// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <windows.h>

#include <crypt.h>
#ifdef _DEBUG
#pragma comment(lib, "cryptd.lib")
#else
#pragma comment(lib, "crypt.lib")
#endif
