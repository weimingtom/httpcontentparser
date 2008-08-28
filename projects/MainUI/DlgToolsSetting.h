#pragma once
#include "afxwin.h"

#include ".\basedlg.h"
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

// CDlgToolsSetting 对话框

class CDlgToolsSetting : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgToolsSetting)

public:
	CDlgToolsSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgToolsSetting();

// 对话框数据
	enum { IDD = IDD_DLG_TOOLS };

	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_staScreenSaver;
	CGuiGroupBox m_staWebContent;
	CGuiGroupBox m_staProgramHistory;
	virtual BOOL OnInitDialog();
};
