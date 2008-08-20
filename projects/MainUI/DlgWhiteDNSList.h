#pragma once
#include "afxwin.h"


#include ".\basedlg.h"
#include "ContentList.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>

class CDlgWhiteDNSList : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgWhiteDNSList)

public:
	CDlgWhiteDNSList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWhiteDNSList();

// 对话框数据
	enum { IDD = IDD_DLG_DNS_WHITELIST };

	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// controls
	CGuiCheckBox m_chkWhiteDNSList;
	CGuiListEdit ListBox;
	RulesList  rules;
public:
	virtual BOOL OnInitDialog();
};
