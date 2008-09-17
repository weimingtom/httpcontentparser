#pragma once

#include ".\basedlg.h"
#include "ContentList.h"
#include <DNSSetting.h>
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include "afxwin.h"

// CDlgBlackDNSList �Ի���

class CDlgBlackDNSList : public CBaseDlg, DNSEnumerator {
	DECLARE_DYNAMIC(CDlgBlackDNSList)

public:
	CDlgBlackDNSList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBlackDNSList();

// �Ի�������
	enum { IDD = IDD_DLG_DNS_RULE };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CGuiCheckBox m_chkEnableDNS;
	CGuiListEdit ListBox;
	RulesList  rules;
	DECLARE_MESSAGE_MAP()

	// ���������
	DNSList black_url_set;

	void initializeData();
	virtual int EnumDNS(const std::string &dns) ;  // member of DNSEnumerator
public:
	virtual BOOL OnInitDialog();
	
};
