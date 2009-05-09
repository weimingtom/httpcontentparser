// MainUIDlg.h : 头文件
//

#pragma once

#include ".\DlgImagerule.h"
#include ".\DlgOnlinehour.h"
#include ".\DlgHelp.h"
#include ".\DlgAbout.h"
#include ".\DlgSearchRule.h"
#include ".\DlgOptions.h"
#include ".\DlgEyecare.h"
#include ".\DlgWhiteDNSList.h"
#include ".\DlgScreenshot.h"
#include ".\DlgWebHistory.h"
#include ".\DlgBlackDNSList.h"
#include ".\DlgProgramControl.h"
#include ".\dlgchangepassword.h"
#include ".\dlgSeachwordlist.h"
#include ".\dlgImageBrowser.h"
#include ".\dlgwebsites.h"
#include ".\dlgcheckpassword.h"
#include ".\Lev1DlgRules.h"
#include ".\Lev1DlgTools.h"
#include ".\basedlg.h"
#include ".\newMenu\NewMenu.h"
#include  ".\Guilib1.5\GuiGroupBox.h"
#include  ".\Guilib1.5\GuiSysTray.h"
#include ".\DlgSwitchChildren.h"
#include ".\dlgregister.h"

#include "afxwin.h"
#include "afxcmn.h"
class CBaseDlg;

// CMainUIDlg 对话框
class CMainUIDlg : public CDialog
{
// 构造
public:
	CMainUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMainUIDlg();
// 对话框数据
	enum { IDD = IDD_MAINUI_DIALOG };

// 实现
protected:
	HICON m_hIcon;
	void setControlsFonts();
	void setRulesDlg();
	void setToolsDlg();
private:
	CTreeCtrl m_treeNavigation;		// 左侧的导航术
	CImageList	m_imageList;			// 导航树上的图标

	void InitTreeNodes();		// 初始化树的节点
	void setCurDlg(const DWORD item);
	void initDlgs();
	void showDlg();

	//
	void ChangeCurDlg(CBaseDlg *dlg);

	// 设置System Tray Menu;
	void setupTrayMenu();

	// dlgs
	CDlgEyecare	m_dlgEyecare;
	CDlgOptions m_dlgOptions;
	// CDlgImageRule m_dlgImageRules;
	CDlgOnlineHour m_dlgOnlineHour;
	CDlgSearchRule m_dlgSearchRule;
	CDlgScreenshot m_dlgScreenSaver;
	CDlgBlackDNSList m_dlgDnsRule;
	CDlgWhiteDNSList m_dlgWhiteDNS;
	CDlgProgramControl m_dlgProgramControl;
	CDlgAbout m_dlgAbout;
	CDlgWebHistory m_dlgWebHistory;
	CBaseDlg	*m_curDlg;

	CLev1DlgTools m_lev1Tools;
	CLev1DlgRules m_lev1Rules;

	// 右侧树的位置
	CRect    m_rectRight;

	// fonts
	CFont	m_fontTree;
	CFont	m_fontTitle;

	// controls
	// system Tray
	CGuiSysTray		m_sysTray;
	CNewMenu		m_trayMenu;
	
	CGuiGroupBox m_staFunFrame;
	CGuiButton m_btnOkBAK; // if remove it, some error happens.
	CImageList image_list_;

	//
	BOOL	m_bShown; // 当前界面是否显示
protected:
	afx_msg void OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	// 按钮项
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMainCancel();
	afx_msg void OnBnClickedApply();
	// 菜单处理项
	afx_msg void OnMainExit();
	afx_msg void OnTraymenuMainui();
	afx_msg void OnMainChangepassword();
	afx_msg void OnMainParents();
	afx_msg void OnMainChildren();
	afx_msg void OnToolsDesktopimage();
	afx_msg void OnMainLockcomputer();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnWebhistoryImages();
	afx_msg void OnWebhistorySearchkeyword();
	afx_msg void OnWebhistoryWebsites();

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
protected:
	// 根据当前状态初始化TrayMenu
	// 此函数会在每次应用程序启动及状态切换时调用
	void UpdateUIStateByModel();

	// 根据当前模式，调整图标
	void AdjustModelIcon();
private:
	// 隐藏或是显示主界面
	void ShowMainUI();
	void HideMainUI(BOOL autoSwitchCheck = TRUE);
	BOOL isShown() const { return m_bShown;}

	// 对话框
	CDlgCheckPassword m_dlgCheckPassword_;
	CDlgChangePassword m_dlgChangePassword_;
	CDlgImageBrowser m_dlgImageBrowser_;
	CDlgSearchWordList m_dlgSearchKeyword_;
	CDlgWebsites m_dlgWebsites_;
	CDlgSwitchChildren m_dlgSwitchChildren_;
	CDlgRegister m_dlgRegister_;

private:
	void SwitchOnClose();
public:
	virtual HRESULT get_accHelp(VARIANT varChild, BSTR *pszHelp);
	afx_msg void OnMainRegister();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
