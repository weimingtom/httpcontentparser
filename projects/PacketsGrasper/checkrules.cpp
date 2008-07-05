#include "stdafx.h"
#include <com\Rules_management_exe.h>
#include <com\Rules_management_exe_i.c>
#include "debug.h"

// 2008.6.8
// 如果spi在firefox中初始化话， 那么dllMain的 DLL_PROCESS_ATTACH中初始化时调用
// CoCreateInstance是会死锁，而IE恰恰相反....
// 只注意这两个进程了，忘了考虑其他进程
// *** 测试，如果强行终止com exe, 会不会直接导致网络应用程序非法操作呢？？？？

namespace {

IExeRulesChecker * pRulesChecker_ = NULL;

const TCHAR IE_PROCESS_NAME[] = _T("iexplore");
const TCHAR FIREFOX_PROCESS_NAME[] = _T("firefox");

};
