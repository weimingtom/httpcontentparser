// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//
#ifndef _TEST_HISTORY_CONTENT_STDAFX_H__
#define _TEST_HISTORY_CONTENT_STDAFX_H__

#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

#include <SearchkeywordUtil.h>

#ifdef _DEBUG
#	pragma comment(lib, "historyContentd.lib")
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "historyContent.lib")
#	pragma comment(lib, "utility.lib")
#endif

#endif  // _TEST_HISTORY_CONTENT_STDAFX_H__