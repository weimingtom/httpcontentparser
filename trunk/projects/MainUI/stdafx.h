// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once				


#define _CRT_SECURE_NO_DEPRECATE

#include <afx.h>
#include <afxcmn.h>
#include <afxcview.h>
#include <afxdlgs.h>
#include <afxdisp.h>
#include <afxtempl.h>
#include <shlwapi.h>
#if _MSC_VER >= 1500
  #include <vsstyle.h>
#endif


#ifdef _DEBUG
#pragma comment(lib, "settingd.lib")
#pragma comment(lib, "apputilityd.lib")
#else
#pragma comment(lib, "apputility.lib")
#endif 

#include "Gdiplus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#pragma comment(lib, "uxtheme.lib")

#include "resource.h"
#include <afxwin.h>


