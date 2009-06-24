#pragma once


// CFirstPwdDlg 对话框

class CFirstPwdDlg : public CDialog
{
	DECLARE_DYNAMIC(CFirstPwdDlg)

public:
	CFirstPwdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirstPwdDlg();

// 对话框数据
	enum { IDD = IDD_POPUP_SETPWDFIRST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	void resetField();
private:
	CString m_strNewPwd;
	CString m_strPwdConfirm;
};
