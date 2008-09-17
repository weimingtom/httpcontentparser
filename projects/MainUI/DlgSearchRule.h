#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include "afxwin.h"

// CDlgSearchRule 对话框

class CDlgSearchRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearchRule();

// 对话框数据
	enum { IDD = IDD_DLG_SEARCH_RULE };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	CGuiListEdit ListBox;
	CGuiCheckBox m_chkEnableSearchChk;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	
};
