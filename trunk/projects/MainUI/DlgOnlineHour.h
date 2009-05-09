#pragma once

#include ".\basedlg.h"
#include ".\Cells.h"
#include <afxwin.h>
#include <Enumerate.h>
// CDlgOnlineHour 对话框

class CDlgOnlineHour : public CBaseDlg {
	DECLARE_DYNAMIC(CDlgOnlineHour)

public:
	CDlgOnlineHour(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOnlineHour();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_DLG_ONLINE_RULE };

	virtual int OnApply();
	virtual void OnShow();

protected:
	CCells cells;
	CButton m_chkTimeCtrl;

	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bEnableTimeCheck;

public:
	afx_msg void OnBnClickedChkTimectrl();
};
