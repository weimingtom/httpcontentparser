// HotKeyTestDlg.h : header file
//

#if !defined(AFX_HOTKEYTESTDLG_H__6B5E385E_3913_45B0_BC4A_CC42845F82AF__INCLUDED_)
#define AFX_HOTKEYTESTDLG_H__6B5E385E_3913_45B0_BC4A_CC42845F82AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHotKeyTestDlg dialog

class CHotKeyTestDlg : public CDialog
{
// Construction
public:
	LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	CHotKeyTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHotKeyTestDlg)
	enum { IDD = IDD_HOTKEYTEST_DIALOG };
	CButton	m_stop;
	CButton	m_start;
	CComboBox	m_virkey;
	CComboBox	m_modifier;
	CString	m_filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotKeyTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHotKeyTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnDestroy();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYTESTDLG_H__6B5E385E_3913_45B0_BC4A_CC42845F82AF__INCLUDED_)
