#pragma once


// CPWDChkDlg �Ի���
#include ".\comutility.h"

class CPWDChkDlg : public CDialog
{
	DECLARE_DYNAMIC(CPWDChkDlg)

public:
	CPWDChkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPWDChkDlg();

// �Ի�������
	enum { IDD = IDD_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnTimer(UINT nIDEvent);
private:
	CString m_strPwd;
public:
	void OnOK() {}
	void OnCancel(){}
};
