// MainUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMainUIApp:
// �йش����ʵ�֣������ MainUI.cpp
//

class CMainUIApp : public CWinApp
{
public:
	CMainUIApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
protected:
	BOOL Initialize(void);
};

extern CMainUIApp theApp;