// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#ifndef _SETTING_STDAFX_H__
#define _SETTING_STDAFX_H__


#include <iostream>
#include <tchar.h>
#include <objbase.h>
#include <windows.h>
#include <comdef.h>


#ifdef _DEBUG

#	pragma comment(lib, "settingd.lib")
#else 
#	pragma comment(lib, "setting.lib")
#endif


#pragma comment(lib, "ws2_32.lib")

#endif  // _SETTING_STDAFX_H__