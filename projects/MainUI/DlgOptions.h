#pragma once

#include ".\basedlg.h"
#include <afxcmn.h>
#include "afxcmn.h"
#include "afxwin.h"
#include "AutoTraHotKeyCtrl.h"

// CDlgOptions 对话框

class CDlgOptions : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgOptions)

public:
	CDlgOptions(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOptions();

	virtual std::string getHelpLink() const;

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
	afx_msg void OnBnClickedChkSwitchchildrenWhenClose();
	afx_msg void OnBnClickedChkAskmeAgainWhenclose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
protected:
	// control variables
	CButton m_chkAutoLoad;
	CStatic m_staSystemOption;
	CStatic m_staHotkey;
	CAutoTraHotKeyCtrl m_hotkeyLaunch;
	CAutoTraHotKeyCtrl m_hotKeyShowDlg;
	CAutoTraHotKeyCtrl m_hotkeySwitchUser;

	BOOL m_bAutoRun;
	BOOL m_bOld_autorun;

	BOOL m_bSwitchToChildrenOnClose;
	BOOL m_bAskmeOnClose;
protected:
	void SetAutoRun();
	int setHotKey();

	int setMisc();
};
