#pragma once
#include ".\basedlg.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiEdit.h>
#include "afxwin.h"
#include "afxcmn.h"


// CDlgWebHistory �Ի���
class CDlgWebHistory : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgWebHistory)

public:
	CDlgWebHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWebHistory();

// �Ի�������
	enum { IDD = IDD_DLG_WEB_HISTORY };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	void ChangeRecordType();

	// ��ʼ��
	void initializeSetting();
public:
	afx_msg void OnBnClickedBunClearCache();
	afx_msg void OnBnClickedBtnHistoryPages();
	afx_msg void OnBnClickedBtnHistoryImage();
	virtual BOOL OnInitDialog();


	CButton m_btnExportWebSiteList;
	CButton m_btnViewtheHistory;
	CButton m_btnClearCache;
	CGuiGroupBox m_staTools;
	CGuiGroupBox m_staHistory;
	CGuiGroupBox m_staTypes;
	CSliderCtrl m_sliderWebHistoryAutoClean;

	// constrols
	BOOL m_bPornImage;
	BOOL m_bPornPage;
	BOOL m_bPornWebsite;
	BOOL m_bAllImage;
	BOOL m_bAllPages;
	BOOL m_bAllWebsite;
};
