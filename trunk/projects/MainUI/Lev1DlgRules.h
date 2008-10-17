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

class CLev1DlgRules : public CBaseDlg {
	DECLARE_DYNAMIC(CLev1DlgRules)

public:
	CLev1DlgRules(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLev1DlgRules();

// 对话框数据
	enum { IDD = IDD_LEV1_RULE };

	
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strComment;
	CEdit m_edit;
	CGuiGroupBox m_staComment;
};
