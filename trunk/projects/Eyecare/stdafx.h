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
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "winlockd.lib")
#pragma comment(lib, "loggerd.lib")
#else
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "winlock.lib")
#pragma comment(lib, "logger.lib")
#endif
