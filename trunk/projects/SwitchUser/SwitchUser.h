// SwitchUser.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CSwitchUserApp:
// �йش����ʵ�֣������ SwitchUser.cpp
//

class CSwitchUserApp : public CWinApp
{
public:
	CSwitchUserApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSwitchUserApp theApp;
