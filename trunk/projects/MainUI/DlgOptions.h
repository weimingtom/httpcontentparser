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

// CDlgOptions �Ի���

class CDlgOptions : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgOptions)

public:
	CDlgOptions(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOptions();

// �Ի�������
	enum { IDD = IDD_DLG_OPTION };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkAutoload();

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

	BOOL m_bAutoRun;
	BOOL m_bOld_autorun;
protected:
	// �����ȼ�
	WORD m_wLaunchKey, m_wLaunchModifier;
	WORD m_wMainUIKey, m_wMainUIModifier;
	WORD m_wSwitchUserKey, m_wSwitchUserModifier;
protected:
	void SetAutoRun();
	void setHotKey();
};
