// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#ifndef _TEST_SELECTIO_STDAFX_H__
#define _TEST_SELECTIO_STDAFX_H__

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

#include "..\..\projects\PacketsGrasper\SelectIO.h"

#ifdef _DEBUG
#	pragma comment(lib, "cppunitd.lib")
#	pragma comment(lib, "testrunnerd.lib")
#	pragma comment(lib, ".\\SelectIODebug\\selectiod.lib")
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "apputilityd.lib")
#else 
#	pragma comment(lib, "TestRunner.lib")
#	pragma comment(lib, "cppunit.lib")
#	pragma comment(lib, ".\selectiorelease\selectio.lib")
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "apputility.lib")
#endif

#endif  // _TEST_SELECTIO_STDAFX_H__