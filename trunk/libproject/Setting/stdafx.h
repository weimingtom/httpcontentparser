// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <windows.h>
#include <string>
#include <map>
#include <set>
#include <vector>

#pragma comment(lib, "zlib.lib")

#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "sysutilityd.lib")
#	pragma comment(lib, "tinyxmld_STL.lib")

#else
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "sysutility.lib")
#	pragma comment(lib, "tinyxml_STL.lib")
#endif

