#pragma once

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
#include <afxcmn.h>
#include "afxcmn.h"
#include "afxwin.h"

// CDlgOptions 对话框

class CDlgOptions : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgOptions)

public:
	CDlgOptions(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOptions();

// 对话框数据
	enum { IDD = IDD_DLG_OPTION };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedChkAutoload();
	afx_msg void OnBnClickedChkEnableTimeoutSwitch();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
protected:
	// control variables
	CButton m_chkAutoLoad;
	CGuiGroupBox m_staSystemOption;
	CGuiGroupBox m_staOthers;
	CGuiGroupBox m_staHotkey;
	CHotKeyCtrl m_hotkeyLaunch;
	CHotKeyCtrl m_hotKeyShowDlg;
	CHotKeyCtrl m_hotkeySwitchUser;
	CStatic m_staTimeoutValue;
	CSliderCtrl m_sldTimeout;

	BOOL m_bAutoRun;
	BOOL m_bOld_autorun;
protected:
	void SetAutoRun();
	int setHotKey();
	int setAutoswitch();
	int restoreAutoswitchSetting();
	
	// 更新状态
	void UpdateAutoswitchState();
};
