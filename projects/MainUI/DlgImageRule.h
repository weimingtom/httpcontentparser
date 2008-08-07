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

// CDlgImageRule 对话框

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImageRule();

// 对话框数据
	enum { IDD = IDD_DLG_IMAGERULES };

	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiCheckBox m_chkImage;
	CGuiCheckBox m_chkShowImage;
	CGuiCheckBox m_chkJPEG;
	CGuiCheckBox m_chkGIF;
	CGuiCheckBox m_chkBMP;
	CGuiCheckBox m_chkPNG;
	
	CGuiGroupBox m_staImageCheck;
	CGuiGroupBox m_staImageSize;
	CGuiGroupBox m_staImageType;
	CGuiEdit m_editImageScale;

	BOOL m_bShowImage;
	BOOL m_bCheckImage;

	virtual BOOL OnInitDialog();
};
