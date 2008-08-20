#pragma once

#include ".\basedlg.h"
#include "ContentList.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include "afxwin.h"

// CDlgDNSRule 对话框

class CDlgDNSRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgDNSRule)

public:
	CDlgDNSRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDNSRule();

// 对话框数据
	enum { IDD = IDD_DLG_DNS_RULE };

	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CGuiCheckBox m_chkEnableDNS;
	CGuiListEdit ListBox;
	RulesList  rules;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
};
