#pragma once


// CPopTipRegDlg �Ի���

class CPopTipRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopTipRegDlg)

public:
	CPopTipRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPopTipRegDlg();

// �Ի�������
	enum { IDD = IDD_POP_TIPREG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBesn();
	afx_msg void OnBnClickedBtnBuynow();
};
