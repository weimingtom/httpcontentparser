#ifndef _UNINSTALL_CDLGCHECKPASSWORD_H__
#define _UNINSTALL_CDLGCHECKPASSWORD_H__

#include ".\resource.h"
// CDlgCheckPassword �Ի���

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCheckPassword();

// �Ի�������
	enum { IDD = IDD_POPDLG_CHKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
