// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#ifndef STRICT
#define STRICT
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows 95 �� Windows NT 4 ����߰汾�Ĺ��ܡ�
#define WINVER 0x0400		// ���˸���Ϊ����� Windows 98 �� Windows 2000 ����߰汾�ĺ��ʵ�ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows NT 4 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0400	// ���˸���Ϊ����� Windows 2000 ����߰汾�ĺ��ʵ�ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ���˸���Ϊ����� Windows Me ����߰汾�ĺ��ʵ�ֵ��
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯����Ϊ��ʽ��

// �ر� ATL ��ĳЩ������ȫ���Եĳ���������Ϣ������
#define _ATL_ALL_WARNINGS


#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <crypt.h>

#ifdef _DEBUG
#	pragma comment(lib, "settingd.lib")
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "ScreenRecord_d.lib")
#	pragma comment(lib, "historyContentd.lib")
#	pragma comment(lib, "cryptd.lib")
#	pragma comment(lib, "shextUtilityd.lib")
#	pragma comment(lib, "softwareencryptd.lib")
# pragma comment(lib, "loggerd.lib")
#else 
#	pragma comment(lib, "setting.lib")
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "ScreenRecord.lib")
#	pragma comment(lib, "historyContent.lib")
#	pragma comment(lib, "crypt.lib")
#	pragma comment(lib, "shextUtility.lib")
#	pragma comment(lib, "softwareencrypt.lib")
# pragma comment(lib, "logger.lib")
#endif


using namespace ATL;
