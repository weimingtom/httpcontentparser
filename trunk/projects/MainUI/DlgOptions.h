#pragma once

#include ".\basedlg.h"
#include  ".\Guilib1.5\GuiGroupBox.h"
#include <afxcmn.h>
#include "afxcmn.h"
#include "afxwin.h"

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedChkAutoload();
	afx_msg void OnBnClickedChkSwitchchildrenWhenClose();
	afx_msg void OnBnClickedChkAskmeAgainWhenclose();

	DECLARE_MESSAGE_MAP()
protected:
	// control variables
	CButton m_chkAutoLoad;
	CGuiGroupBox m_staSystemOption;
	CGuiGroupBox m_staHotkey;
	CHotKeyCtrl m_hotkeyLaunch;
	CHotKeyCtrl m_hotKeyShowDlg;
	CHotKeyCtrl m_hotkeySwitchUser;

	BOOL m_bAutoRun;
	BOOL m_bOld_autorun;

	BOOL m_bSwitchToChildrenOnClose;
	BOOL m_bAskmeOnClose;
protected:
	void SetAutoRun();
	int setHotKey();

	int setMisc();
};
