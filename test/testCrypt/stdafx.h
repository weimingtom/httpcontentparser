// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <windows.h>

#include <crypt.h>
#ifdef _DEBUG
#pragma comment(lib, "cryptd.lib")
#else
#pragma comment(lib, "crypt.lib")
#endif
