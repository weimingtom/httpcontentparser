#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include <Enumerate.h>
#include <string>
#include "afxwin.h"
#include ".\ContentList.h"

// CDlgSearchRule 对话框
class CDlgSearchRule : public CBaseDlg, Enumerator1<std::string>, RuleChanged {
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearchRule();

// 对话框数据
	enum { IDD = IDD_DLG_SEARCH_RULE };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();

	virtual BOOL OnInitDialog();
protected:
	// 初始化初始设置
	void initializeData();
	virtual int Enum(const std::string &dns) ;  // member of DNSEnumerator

	CGuiListEdit ListBox;
	CButton m_chkEnableSearchChk;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

	// control variable
	BOOL m_bEnableSearchRule;
	BOOL m_bChkGoogle;
	BOOL m_bChkYahoo;
	BOOL m_bChkBaidu;
public:
	virtual void OnAddItem(const CString &str);
	virtual void OnDelItem(const CString &str);
	virtual bool ValidateItem(const CString & str, CString &output);
	RulesList  rules;
};
