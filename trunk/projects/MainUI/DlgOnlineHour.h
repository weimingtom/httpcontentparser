#pragma once

#include ".\basedlg.h"
// CDlgOnlineHour 对话框

class CDlgOnlineHour : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgOnlineHour)

public:
	CDlgOnlineHour(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOnlineHour();

// 对话框数据
	enum { IDD = IDD_DLG_ONLINE_RULE };

	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
