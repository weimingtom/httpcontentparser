// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <windows.h>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <atltime.h>
#pragma comment(lib, "zlib.lib")

#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "tinyxmld_STL.lib")
#else
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "tinyxml_STL.lib")
#endif

