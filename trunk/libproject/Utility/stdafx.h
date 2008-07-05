// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料

	
#include <string>
#include <tchar.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <syncobject/SyncObject.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#ifdef _DEBUG
#	pragma comment(lib, "ThreadSyncd.lib")
#else
#	pragma comment(lib, "ThreadSync.lib")
#endif