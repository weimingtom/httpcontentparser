#pragma once


// CFirstPwdDlg �Ի���

class CFirstPwdDlg : public CDialog
{
	DECLARE_DYNAMIC(CFirstPwdDlg)

public:
	CFirstPwdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirstPwdDlg();

// �Ի�������
	enum { IDD = IDD_POPUP_SETPWDFIRST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	void resetField();
private:
	CString m_strNewPwd;
	CString m_strPwdConfirm;
};
