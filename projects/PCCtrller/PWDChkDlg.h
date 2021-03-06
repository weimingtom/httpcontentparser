#pragma once


// CPWDChkDlg 对话框
#include ".\comutility.h"

class CPWDChkDlg : public CDialog
{
	DECLARE_DYNAMIC(CPWDChkDlg)

public:
	CPWDChkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPWDChkDlg();

// 对话框数据
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnTimer(UINT nIDEvent);

	void OnOK() {}
	void OnCancel(){}
private:
	CString m_strPwd;

	// 注意在Eyecare和LockPC模式下应该调用两个不同的函数
	BOOL checkPwd();
};
