#ifndef _MAINUI_CDLGCHECKPASSWORD_H__
#define _MAINUI_CDLGCHECKPASSWORD_H__

#include "afxwin.h"

// CDlgCheckPassword 对话框

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCheckPassword();

// 对话框数据
	enum { IDD = IDD_DLG_CHKPASSWORD };

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
	afx_msg void OnBnClickedOk();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL OnInitDialog();

public:
	bool checkPassword();
};

#endif  // _MAINUI_CDLGCHECKPASSWORD_H__
