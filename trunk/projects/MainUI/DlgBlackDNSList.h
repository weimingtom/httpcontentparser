#pragma once

#include ".\basedlg.h"
#include ".\ContentList.h"
#include <setting\DNSSetting.h>
#include  ".\Guilib1.5\GuiListEdit.h"
#include "afxwin.h"

// CDlgBlackDNSList �Ի���

class CDlgBlackDNSList : public CBaseDlg, RuleChanged {
	DECLARE_DYNAMIC(CDlgBlackDNSList)

public:
	CDlgBlackDNSList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBlackDNSList();

	virtual std::string getHelpLink() const;

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
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkBlackDnslist();
public:
	virtual void OnAddItem(const CString &str);
	virtual void OnDelItem(const CString &str);
	virtual bool ValidateItem(const CString & str, CString &output);
	RulesList  rules;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
