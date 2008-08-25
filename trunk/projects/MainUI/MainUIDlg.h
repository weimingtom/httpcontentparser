// MainUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "dlgimagerule.h"
#include "dlgonlinehour.h"
#include "dlghelp.h"
#include "dlgabout.h"
#include "dlgdnsrule.h"
#include "dlgsearchrule.h"
#include "Lev1DlgRules.h"
#include "DlgOptions.h"
#include "DlgEyecare.h"
#include "DlgWhiteDNSList.h"
#include ".\basedlg.h"
#include "afxwin.h"

#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuisysTray.h>
#include <Guilib1.5\NewMenu.h>

// CMainUIDlg �Ի���
class CMainUIDlg : public CDialog
{
// ����
public:
	CMainUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAINUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void setControlsFonts();
	void setRulesDlg();
private:
	CTreeCtrl m_treeNavigation;
	void InitTreeNodes();		// ��ʼ�����Ľڵ�
	CImageList m_imageList;
	void setCurDlg(const DWORD item);
	void initDlgs();
	void showDlg();

	// ����System Tray Menu;
	void setupTrayMenu();

	// dlgs
	CDlgEyecare	m_dlgEyecare;
	CDlgOptions m_dlgOptions;
	CDlgImageRule m_dlgImageRules;
	CDlgHelp	m_dlgHelp;
	CDlgOnlineHour m_dlgOnlineHour;
	CDlgSearchRule m_dlgSearchRule;
	CDlgDNSRule m_dlgDnsRule;
	CDlgWhiteDNSList m_dlgWhiteDNS;
	CDlgAbout m_dlgAbout;
	CBaseDlg	*m_curDlg;
	CLev1DlgRules m_lev1Rules;

	// �Ҳ�
	CRect    m_rectRight;

	// fonts
	CFont	m_fontTree;
	CFont	m_fontTitle;

	// controls
	// system Tray
	CGuiSysTray		m_sysTray;
	CMenu		m_trayMenu;
	
	CGuiGroupBox m_staFunFrame;
	CGuiButton m_btnOk;
	CGuiButton m_btnCancel;
	CGuiButton m_btnApply;
	//
	BOOL	m_bShowed; // ��ǰ�����Ƿ���ʾ
protected:
	afx_msg void OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedApply();
	
public:
	afx_msg void OnTraymenuSwitch();
	afx_msg void OnTraymenuMainui();
	afx_msg void OnMainExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
