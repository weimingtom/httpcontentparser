#pragma once

#include ".\basedlg.h"
#include "GuiListEdit.h"
#include "GuiDropDownEdit.h"

// CDlgDNSRule �Ի���

class CDlgDNSRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgDNSRule)

public:
	CDlgDNSRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDNSRule();

// �Ի�������
	enum { IDD = IDD_DLG_DNS_RULE };

protected:
	CGuiListEdit ListBox;
	CGuiDropDownEdit m_edit;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
