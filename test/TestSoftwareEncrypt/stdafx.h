// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <softwareEncrypt\baseEncrypt.h>

#ifdef _DEBUG
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "softwareencryptd.lib")
#else 
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "softwareencrypt.lib")
#endif
