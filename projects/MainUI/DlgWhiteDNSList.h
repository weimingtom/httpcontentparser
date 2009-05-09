#pragma once
#include "afxwin.h"


#include ".\basedlg.h"
#include "ContentList.h"
#include <DNSSetting.h>
#include  ".\Guilib1.5\GuiGroupBox.h"
#include  ".\Guilib1.5\GuiListEdit.h"
#include <Enumerate.h>

class CDlgWhiteDNSList : public CBaseDlg, RuleChanged {
	DECLARE_DYNAMIC(CDlgWhiteDNSList)

public:
	CDlgWhiteDNSList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWhiteDNSList();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_DLG_DNS_WHITELIST };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// controls
	CButton m_chkWhiteDNSList;
	CGuiListEdit ListBox;
	BOOL m_bEnableWhiteDNS;

protected:
	void restoreSetting();
public:
	virtual BOOL OnInitDialog();
	BOOL m_bCheckDenyAllOthers;
	afx_msg void OnBnClickedChkDenyOthers();
	afx_msg void OnBnClickedChkWhiteDnslist();

// DNS Rules
public:
	virtual void OnAddItem(const CString &str);
	virtual void OnDelItem(const CString &str);
	virtual bool ValidateItem(const CString & str, CString &output);
	RulesList  rules;
};
