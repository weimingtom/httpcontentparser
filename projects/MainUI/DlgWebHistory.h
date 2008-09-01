#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiEdit.h>
#include "afxwin.h"


// CDlgWebHistory �Ի���
class CDlgWebHistory : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgWebHistory)

public:
	CDlgWebHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWebHistory();

// �Ի�������
	enum { IDD = IDD_DLG_WEB_HISTORY };
	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnExportWebSiteList;
	CButton m_btnViewtheHistory;
	CButton m_btnClearCache;
	CGuiGroupBox m_staTools;
	CGuiGroupBox m_staHistory;
	CGuiGroupBox m_staTypes;
};
