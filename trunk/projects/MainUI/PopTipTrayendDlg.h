#pragma once


// CPopTipTrayendDlg �Ի���

class CPopTipTrayendDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopTipTrayendDlg)

public:
	CPopTipTrayendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPopTipTrayendDlg();

// �Ի�������
	enum { IDD = IDD_POP_TRAYENDTIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBesn();
	afx_msg void OnBnClickedBtnBuynow();
};
