// Uninstaller.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Uninstaller.h"
#include ".\dlgcheckpassword.h" 
#include ".\DlgReboot.h"
#include ".\dlgprocess.h"
#include <com\comutility.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUninstallerApp

BEGIN_MESSAGE_MAP(CUninstallerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUninstallerApp construction

CUninstallerApp::CUninstallerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CUninstallerApp object

CUninstallerApp theApp;


// CUninstallerApp initialization

BOOL CUninstallerApp::InitInstance()
{
	AutoInitInScale _auto_scale_;

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CString title, message;
	title.LoadString(AfxGetInstanceHandle(), IDS_TITLE);
	message.LoadString(AfxGetInstanceHandle(), IDS_ASCERTAIN);
	if (IDYES != ::MessageBox(NULL, message, title, MB_YESNO | MB_ICONQUESTION)) {
		return FALSE;
	}

	// CHECK THE password
	CDlgCheckPassword dlgCheckPwd;
	if ( IDOK == dlgCheckPwd.DoModal()) {
		m_pMainWnd = NULL;
		CDlgProcess dlgProc;
		dlgProc.DoModal();

		CDlgReboot dlgReboot;
		dlgReboot.DoModal();
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
