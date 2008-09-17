#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiListEdit.h>
#include <Guilib1.5\GuiDropDownEdit.h>
#include <Guilib1.5\GuiCheckBox.h>
#include "afxwin.h"

// CDlgSearchRule �Ի���

class CDlgSearchRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearchRule();

// �Ի�������
	enum { IDD = IDD_DLG_SEARCH_RULE };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	CGuiListEdit ListBox;
	CGuiCheckBox m_chkEnableSearchChk;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	
};
