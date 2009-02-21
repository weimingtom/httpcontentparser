// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <afxwin.h>
#include <ws2spi.h>
#include <io.h>				

 
#ifdef _DEBUG
#	pragma comment(lib, "tinyxmld.lib")
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "apputilityd.lib")
#else
#	pragma comment(lib, "tinyxml.lib")
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "apputility.lib")
#endif

// TODO: 在此处引用程序要求的附加头文件
