#pragma once

#include ".\basedlg.h"
#include ".\Cells.h"
#include "afxwin.h"
#include <Guilib1.5\GuiCheckBox.h>
// CDlgOnlineHour 对话框

class CDlgOnlineHour : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgOnlineHour)

public:
	CDlgOnlineHour(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOnlineHour();

// 对话框数据
	enum { IDD = IDD_DLG_ONLINE_RULE };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();

	CCells cells;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CGuiCheckBox m_chkTimeCtrl;
};
