// MainUI.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号


// CMainUIApp:
// 有关此类的实现，请参阅 MainUI.cpp
//

class CMainUIApp : public CWinApp
{
public:
	CMainUIApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
protected:
	BOOL Initialize(void);

	ULONG_PTR m_GdiplusToken;
};

extern CMainUIApp theApp;
