#pragma once


// CPopTipRegDlg 对话框

class CPopTipRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopTipRegDlg)

public:
	CPopTipRegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPopTipRegDlg();

// 对话框数据
	enum { IDD = IDD_POP_TIPREG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBesn();
	afx_msg void OnBnClickedBtnBuynow();
};
