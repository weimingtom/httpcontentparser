// HotKeyTest.h : main header file for the HOTKEYTEST application
//

#if !defined(AFX_HOTKEYTEST_H__0123E37A_24AE_4A7B_8EC5_E851FFDA4D9E__INCLUDED_)
#define AFX_HOTKEYTEST_H__0123E37A_24AE_4A7B_8EC5_E851FFDA4D9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHotKeyTestApp:
// See HotKeyTest.cpp for the implementation of this class
//

class CHotKeyTestApp : public CWinApp
{
public:
	CHotKeyTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotKeyTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHotKeyTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYTEST_H__0123E37A_24AE_4A7B_8EC5_E851FFDA4D9E__INCLUDED_)
