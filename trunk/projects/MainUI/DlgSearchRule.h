#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>

// CDlgSearchRule �Ի���

class CDlgSearchRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearchRule();

// �Ի�������
	enum { IDD = IDD_DLG_SEARCH_RULE };

	virtual void OnApply();
	virtual void OnShow();
protected:
	CGuiListEdit ListBox;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};
