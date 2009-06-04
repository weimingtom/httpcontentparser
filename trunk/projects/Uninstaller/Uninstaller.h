// Uninstaller.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CUninstallerApp:
// See Uninstaller.cpp for the implementation of this class
//

class CUninstallerApp : public CWinApp
{
public:
	CUninstallerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUninstallerApp theApp;