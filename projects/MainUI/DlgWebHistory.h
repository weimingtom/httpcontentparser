#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiEdit.h>
#include "afxwin.h"
#include "afxcmn.h"


// CDlgWebHistory 对话框
class CDlgWebHistory : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgWebHistory)

public:
	CDlgWebHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebHistory();

// 对话框数据
	enum { IDD = IDD_DLG_WEB_HISTORY };

	virtual int OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void ChangeRecordType();

	// 初始化
	virtual void restoreSetting();
public:
	afx_msg void OnBnClickedBunClearCache();
	afx_msg void OnBnClickedBtnHistoryPages();
	afx_msg void OnBnClickedBtnHistoryImage();
	virtual BOOL OnInitDialog();

protected:
	void updateSta();

	CButton m_btnExportWebSiteList;
	CButton m_btnViewtheHistory;
	CButton m_btnClearCache;
	CGuiGroupBox m_staTools;
	CGuiGroupBox m_staHistory;
	CGuiGroupBox m_staTypes;
	CSliderCtrl m_sliderWebHistoryAutoClean;
	CString m_strAutoClean;

	// constrols
	BOOL m_bPornImage;
	BOOL m_bPornPage;
	BOOL m_bPornWebsite;
	BOOL m_bAllImage;
	BOOL m_bAllPages;
	BOOL m_bAllWebsite;
	
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedChkPronImage();
	afx_msg void OnBnClickedChkPornPage();
	afx_msg void OnBnClickedChkPornWebsites();
	afx_msg void OnBnClickedChkAllImage();
	afx_msg void OnBnClickedChkAllpages();
	afx_msg void OnBnClickedChkAllwebsites();
};
