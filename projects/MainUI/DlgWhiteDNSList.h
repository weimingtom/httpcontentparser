#pragma once
#include "afxwin.h"


#include ".\basedlg.h"
#include "ContentList.h"
#include <DNSSetting.h>
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>

class CDlgWhiteDNSList : public CBaseDlg, DNSEnumerator {
	DECLARE_DYNAMIC(CDlgWhiteDNSList)

public:
	CDlgWhiteDNSList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWhiteDNSList();

// 对话框数据
	enum { IDD = IDD_DLG_DNS_WHITELIST };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// controls
	CGuiCheckBox m_chkWhiteDNSList;
	CGuiListEdit ListBox;
	RulesList  rules;

	// 保存白名单
	DNSList white_url_set;

	void initializeData();
	virtual int EnumDNS(const std::string &dns) ;  // member of DNSEnumerator
public:
	virtual BOOL OnInitDialog();
};
