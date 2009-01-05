// MainUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "dlgimagerule.h"
#include "dlgonlinehour.h"
#include "dlghelp.h"
#include "dlgabout.h"
#include "dlgsearchrule.h"
#include "Lev1DlgRules.h"
#include "DlgOptions.h"
#include "DlgEyecare.h"
#include "DlgWhiteDNSList.h"
#include "DlgScreenshot.h"
#include "DlgWebHistory.h"
#include "DlgBlackDNSList.h"
#include "Lev1DlgTools.h"
#include ".\basedlg.h"
#include "afxwin.h"

#include  ".\Guilib1.5\GuiGroupBox.h"
#include  ".\Guilib1.5\GuiSysTray.h"

class CBaseDlg;

// CMainUIDlg �Ի���
class CMainUIDlg : public CDialog
{
// ����
public:
	CMainUIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMainUIDlg();
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
	void setToolsDlg();
private:
	CTreeCtrl m_treeNavigation;
	void InitTreeNodes();		// ��ʼ�����Ľڵ�
	CImageList m_imageList;
	void setCurDlg(const DWORD item);
	void initDlgs();
	void showDlg();

	//
	void ChangeCurDlg(CBaseDlg *dlg);

	// ����System Tray Menu;
	void setupTrayMenu();

	// dlgs
	CDlgEyecare	m_dlgEyecare;
	CDlgOptions m_dlgOptions;
	CDlgImageRule m_dlgImageRules;
	CDlgOnlineHour m_dlgOnlineHour;
	CDlgSearchRule m_dlgSearchRule;
	CDlgScreenshot m_dlgScreenSaver;
	CDlgBlackDNSList m_dlgDnsRule;
	CDlgWhiteDNSList m_dlgWhiteDNS;
	CDlgAbout m_dlgAbout;
	CDlgWebHistory m_dlgWebHistory;
	CBaseDlg	*m_curDlg;

	CLev1DlgTools m_lev1Tools;
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
	CGuiButton m_btnOkBAK; // if remove it, some error happens.
	CImageList image_list_;

	//
	BOOL	m_bShown; // ��ǰ�����Ƿ���ʾ
protected:
	afx_msg void OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);

	// ��ť��
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMainCancel();
	afx_msg void OnBnClickedApply();
	// �˵�������
	afx_msg void OnMainExit();
	afx_msg void OnTraymenuMainui();
	afx_msg void OnMainChangepassword();
	afx_msg void OnMainParents();
	afx_msg void OnMainChildren();
	afx_msg void OnToolsDesktopimage();
	afx_msg void OnToolsWebhistory();
	afx_msg void OnMainLockcomputer();
	afx_msg void OnDestroy();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	virtual void OnOK();
	virtual void OnCancel();
protected:
	// ���ݵ�ǰ״̬��ʼ��TrayMenu
	// �˺�������ÿ��Ӧ�ó���������״̬�л�ʱ����
	void UpdateUIStateByModel();
private:
	void ShowMainUI();
	void HideMainUI();
	BOOL isShown() const { return m_bShown;}
public:
	afx_msg void OnTimer(UINT nIDEvent);
};