// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <comdef.h>


#ifdef _DEBUG
#pragma comment(lib, "apputilityd.lib")
#pragma comment(lib, "cryptd.lib")
#else
#pragma comment(lib, "crypt.lib")
#pragma comment(lib, "apputility.lib")
#endif

