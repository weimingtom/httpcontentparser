#pragma once

#include ".\basedlg.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>

// CDlgDNSRule �Ի���

class CDlgDNSRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgDNSRule)

public:
	CDlgDNSRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDNSRule();

// �Ի�������
	enum { IDD = IDD_DLG_DNS_RULE };

	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CGuiListEdit ListBox;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
