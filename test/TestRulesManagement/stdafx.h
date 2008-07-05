#ifndef _TEST_RULES_MANAGEMENT_STDAFX_H__
#define _TEST_RULES_MANAGEMENT_STDAFX_H__

#define _WIN32_WINNT 0x0400



#include <iostream>
#include <tchar.h>

#include <cppunit\extensions\HelperMacros.h>
#include <cppunit\ui\text\TestRunner.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\TestResult.h>
#include <cppunit\TestResultCollector.h>
#include <cppunit\BriefTestProgressListener.h>
#include <cppunit\CompilerOutputter.h> 
#include <objbase.h>
#include <windows.h>
#include <comdef.h>

#ifdef _DEBUG
#	pragma comment(lib, "cppunitd.lib")
#	pragma comment(lib, "testrunnerd.lib")
#else 
#	pragma comment(lib, "TestRunner.lib")
#	pragma comment(lib, "cppunit.lib")
#endif

#pragma comment(lib, "ws2_32.lib")

#endif  // _TEST_RULES_MANAGEMENT_STDAFX_H__
