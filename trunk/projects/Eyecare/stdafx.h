// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define		WINVER 0x0400
#define    _WIN32_WINNT 0x0400

// Windows ͷ�ļ�:
#include <windows.h>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include   <commctrl.h>

#ifdef _DEBUG
#	pragma comment(lib, "sysutilityd.lib")
#	pragma comment(lib, "syshookd.lib")
#else
#	pragma comment(lib, "sysutility.lib")
#	pragma comment(lib, "syshook.lib")
#endif
