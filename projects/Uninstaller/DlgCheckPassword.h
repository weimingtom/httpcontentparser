#ifndef _UNINSTALL_CDLGCHECKPASSWORD_H__
#define _UNINSTALL_CDLGCHECKPASSWORD_H__

#include ".\resource.h"
// CDlgCheckPassword 对话框

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCheckPassword();

// 对话框数据
	enum { IDD = IDD_POPDLG_CHKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtPassword;
	CString m_strPassword;
	CButton m_btnOk;
	CButton m_btnCancel;
	HICON m_hIcon;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	bool checkPassword();
};

#endif  // _UNINSTALL_CDLGCHECKPASSWORD_H__
