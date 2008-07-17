#pragma once

#include ".\basedlg.h"
#include "GuiListEdit.h"
#include "GuiDropDownEdit.h"

// CDlgDNSRule 对话框

class CDlgDNSRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgDNSRule)

public:
	CDlgDNSRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDNSRule();

// 对话框数据
	enum { IDD = IDD_DLG_DNS_RULE };

protected:
	CGuiListEdit ListBox;
	CGuiDropDownEdit m_edit;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
