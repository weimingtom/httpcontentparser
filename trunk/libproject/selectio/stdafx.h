// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <winsock2.h>
#include <ws2spi.h>
#include <io.h>				
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

#include <com\comutility.h>

#ifdef _DEBUG
#	pragma comment(lib, "utilitymtd.lib")
#else
#	pragma comment(lib, "utilitymt.lib")
#endif

// TODO: 在此处引用程序要求的附加头文件
