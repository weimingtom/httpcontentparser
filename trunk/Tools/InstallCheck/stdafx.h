// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <windows.h>

#include <apputility.h>
#include <AppInstallValidate.h>


#ifndef DEBUG
#pragma comment(lib, "Apputility.lib")
#else
#pragma comment(lib, "Apputilityd.lib")
#endif