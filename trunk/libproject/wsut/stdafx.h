// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#include <windows.h>
#include <tchar.h>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>


#pragma comment(lib, "log4cxx.lib")

#ifdef _DEBUG
#pragma comment(lib, "apputilityd.lib")
#else
#pragma comment(lib, "apputility.lib")
#endif