#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiEdit.h>
#include "afxwin.h"


// CDlgWebHistory 对话框
class CDlgWebHistory : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgWebHistory)

public:
	CDlgWebHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebHistory();

// 对话框数据
	enum { IDD = IDD_DLG_WEB_HISTORY };
	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void ChangeRecordType();
public:
	afx_msg void OnBnClickedBunClearCache();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnExportWebsites();

	CGuiButton m_btnExportWebSiteList;
	CGuiButton m_btnViewtheHistory;
	CGuiButton m_btnClearCache;
	CGuiGroupBox m_staTools;
	CGuiGroupBox m_staHistory;
	CGuiGroupBox m_staTypes;

	// constrols
	BOOL m_bPornImage;
	BOOL m_bPornPage;
	BOOL m_bPornWebsite;
	BOOL m_bAllImage;
	BOOL m_bAllPages;
	BOOL m_bAllWebsite;
};
