// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯����Ϊ��ʽ��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <conio.h>
#include <process.h>
#include <assert.h>

#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "utility.lib")
#endif
