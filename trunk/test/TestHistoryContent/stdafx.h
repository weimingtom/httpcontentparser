// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//
#ifndef _TEST_HISTORY_CONTENT_STDAFX_H__
#define _TEST_HISTORY_CONTENT_STDAFX_H__

#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>

#include <cppunit\extensions\HelperMacros.h>
#include <cppunit\ui\text\TestRunner.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\TestResult.h>
#include <cppunit\TestResultCollector.h>
#include <cppunit\BriefTestProgressListener.h>
#include <cppunit\CompilerOutputter.h> 

#include <SearchkeywordUtil.h>

#ifdef _DEBUG
#	pragma comment(lib, "cppunitd.lib")
#	pragma comment(lib, "testrunnerd.lib")
#	pragma comment(lib, "historyContentd.lib")
#else 
#	pragma comment(lib, "TestRunner.lib")
#	pragma comment(lib, "cppunit.lib")
#	pragma comment(lib, "historyContent.lib")
#endif

#endif  // _TEST_HISTORY_CONTENT_STDAFX_H__