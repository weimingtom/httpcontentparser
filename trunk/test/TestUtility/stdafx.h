// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>

#include <winsock2.h>
#include <objbase.h>
#include <windows.h>
#include <comdef.h>

#include "utility\ProtocolPacket.h"

#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#else 
#	pragma comment(lib, "utility.lib")
#endif
