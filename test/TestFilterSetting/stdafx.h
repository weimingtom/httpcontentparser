// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#include <iostream>
#include <tchar.h>

#include <objbase.h>
#include <windows.h>
#include <comdef.h>

#ifdef _DEBUG
#	pragma comment(lib, "settingd.lib")
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "utility.lib")
#endif
