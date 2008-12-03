#pragma once
#include ".\basedlg.h"
#include "afxwin.h"

#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiComboBoxExt.h>
#include <Guilib1.5\GuiLinkButton.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiSliderCtrl.h>
#include <Guilib1.5\GuiMiniTool.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiRadioButton.h>
#include <Guilib1.5\GuiComboFont.h>
#include "afxcmn.h"

// CDlgImageRule �Ի���

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageRule();

// �Ի������� 
	enum { IDD = IDD_DLG_IMAGERULES };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	CButton m_chkJPEG;
	CButton m_chkGIF;
	CButton m_chkBMP;
	CButton m_chkPNG;
	
	CGuiGroupBox m_staImageCheck;
	CGuiGroupBox m_staImageSize;
	CGuiGroupBox m_staImageType;
	CGuiEdit m_editImageScale;
	CSliderCtrl m_sliderImageCheckDegree;

	BOOL m_bCheckGIF;
	BOOL m_bCheckJPEG;
	BOOL m_bCheckBMP;
	BOOL m_bCheckPNG;
public:
	afx_msg void OnBnClickedChkJpeg();
	afx_msg void OnBnClickedChkGif();
	afx_msg void OnBnClickedChkBmp();
	afx_msg void OnBnClickedChkPng();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

};