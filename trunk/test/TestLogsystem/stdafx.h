// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#ifndef _TEST_LOGSTSTEM_STDAFX_H__
#define _TEST_LOGSTSTEM_STDAFX_H__

#include <iostream>
#include <tchar.h>


#include <cppunit\extensions\HelperMacros.h>
#include <cppunit\ui\text\TestRunner.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\TestResult.h>
#include <cppunit\TestResultCollector.h>
#include <cppunit\BriefTestProgressListener.h>
#include <cppunit\CompilerOutputter.h> 


#ifdef _DEBUG
#	pragma comment(lib, "cppunitd.lib")
#	pragma comment(lib, "testrunnerd.lib")
#	pragma comment(lib, "logsystemd.lib")
#	pragma comment(lib, "ThreadSyncd.lib")
#else 
#	pragma comment(lib, "TestRunner.lib")
#	pragma comment(lib, "cppunit.lib")
#	pragma comment(lib, "logsystem.lib")
#	pragma comment(lib, "ThreadSync.lib")
#endif

#pragma warning( disable : 4204)
#endif