#pragma once
#include "afxwin.h"


#include ".\basedlg.h"
#include "ContentList.h"
#include <DNSSetting.h>
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include <Enumerate.h>

class CDlgWhiteDNSList : public CBaseDlg, Enumerator1<std::string> {
	DECLARE_DYNAMIC(CDlgWhiteDNSList)

public:
	CDlgWhiteDNSList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWhiteDNSList();

// �Ի�������
	enum { IDD = IDD_DLG_DNS_WHITELIST };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	// controls
	CButton m_chkWhiteDNSList;
	CGuiListEdit ListBox;
	RulesList  rules;

	BOOL m_bEnableWhiteDNS;

	void initializeData();
	virtual int Enum(const std::string &dns) ;  // member of DNSEnumerator
public:
	virtual BOOL OnInitDialog();
};
