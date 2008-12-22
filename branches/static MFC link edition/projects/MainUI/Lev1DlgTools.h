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

// CLev1DlgTools 对话框

class CLev1DlgTools : public CBaseDlg
{
	DECLARE_DYNAMIC(CLev1DlgTools)

public:
	CLev1DlgTools(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLev1DlgTools();

// 对话框数据
	enum { IDD = IDD_LEV1_TOOLS };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
