// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <softwareEncrypt\baseEncrypt.h>

#ifdef _DEBUG
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "softwareencryptd.lib")
#else 
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "softwareencrypt.lib")
#endif
