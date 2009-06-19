#pragma once


// CPopTipTrayendDlg 对话框

class CPopTipTrayendDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopTipTrayendDlg)

public:
	CPopTipTrayendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPopTipTrayendDlg();

// 对话框数据
	enum { IDD = IDD_POP_TRAYENDTIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBesn();
	afx_msg void OnBnClickedBtnBuynow();
};
