// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

	
#include <string>
#include <tchar.h>
#include <syncobject/SyncObject.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#ifdef _DEBUG
#	pragma comment(lib, "ThreadSyncd.lib")
#	pragma comment(lib, "zlib1.lib")
#else
#	pragma comment(lib, "ThreadSync.lib")
#	pragma comment(lib, "zlib1.lib")
#endif