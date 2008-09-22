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

// CDlgImageRule �Ի���

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageRule();

// �Ի������� 
	enum { IDD = IDD_DLG_IMAGERULES };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkImage;
	CButton m_chkShowImage;
	CButton m_chkJPEG;
	CButton m_chkGIF;
	CButton m_chkBMP;
	CButton m_chkPNG;
	
	CGuiGroupBox m_staImageCheck;
	CGuiGroupBox m_staImageSize;
	CGuiGroupBox m_staImageType;
	CGuiEdit m_editImageScale;

	BOOL m_bShowImage;
	BOOL m_bCheckImage;

	virtual BOOL OnInitDialog();
};
