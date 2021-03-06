#pragma once
#include ".\basedlg.h"

// CDlgHelp 对话框

class CDlgHelp : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgHelp)

public:
	CDlgHelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHelp();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_DLG_HELP };

	virtual void restoreSetting();
	virtual INT_PTR OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnKillfocusList1();
	afx_msg void OnLbnSelcancelList1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
