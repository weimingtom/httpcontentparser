#pragma once

#include ".\basedlg.h"
#include ".\ContentList.h"
#include <DNSSetting.h>
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include "afxwin.h"

// CDlgBlackDNSList �Ի���

class CDlgBlackDNSList : public CBaseDlg, Enumerator1<std::string>, RuleChanged {
	DECLARE_DYNAMIC(CDlgBlackDNSList)

public:
	CDlgBlackDNSList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBlackDNSList();

// �Ի�������
	enum { IDD = IDD_DLG_DNS_RULE };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

	CButton m_chkEnableDNS;
	CGuiListEdit ListBox;
	BOOL m_bEnableBlackDNS;

	virtual void restoreSetting();
	virtual int Enum(const std::string &dns) ;  // member of DNSEnumerator
public:
	virtual BOOL OnInitDialog();

public:
	virtual void OnAddItem(const CString &str);
	virtual void OnDelItem(const CString &str);
	virtual bool ValidateItem(const CString & str, CString &output);
	RulesList  rules;
};
