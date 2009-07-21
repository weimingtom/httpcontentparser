// MainUIDlg.h : ͷ�ļ�
//

#pragma once

#include ".\basedlg.h"
#include ".\dlgwebsites.h"
#include ".\dlgcheckpassword.h"
#include ".\newMenu\NewMenu.h"
#include ".\DlgSwitchChildren.h"
#include ".\TrayIconPosition.h"
#include ".\dlgregister.h"
#include ".\RightRegionDlg.h"
#include ".\guilib1.5\guisystray.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <UILib\PPTooltip\PPTooltip.h>

// CMainUIDlg �Ի���
class CMainUIDlg : public CDialog
{
// ����
public:
	CMainUIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMainUIDlg();
// �Ի�������
	enum { IDD = IDD_MAINUI_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;
	void setControlsFonts();
	void setRulesTreeItems();
	void setToolsTreeItems();
private:
	CTreeCtrl m_treeNavigation;		// ���ĵ�����
	CImageList	m_imageList;			// �������ϵ�ͼ��

	void InitTreeNodes();		// ��ʼ�����Ľڵ�

	// �������ݷ�Ϊ�����֣����ֽڱ���IDI�� ���ֽڱ���IDS
	void setItemData(HTREEITEM hItem, WORD ids, WORD idi);
	WORD getItemIcon();
	WORD getItemIDS();


	CRightRegionDlg m_dlgRight;

	// ����System Tray Menu;
	void setupTrayMenu();

	// �Ҳ�����λ��
	CRect    m_rectRight;

	// fonts
	CFont	m_fontTree;
	
	CGuiSysTray		m_sysTray;
	CNewMenu		m_trayMenu;
	
	CStatic m_staFunFrame;
	CGuiButton m_btnOkBAK; // if remove it, some error happens.
	CImageList image_list_;

	//
	BOOL	m_bShown; // ��ǰ�����Ƿ���ʾ
protected:
	afx_msg void OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

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
	afx_msg void OnMainLockcomputer();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnWebhistoryImages();
	afx_msg void OnWebhistorySearchkeyword();
	afx_msg void OnWebhistoryWebsites();
	afx_msg void OnMainRegister();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnShowServerMsg(WPARAM, LPARAM);
	virtual HRESULT get_accHelp(VARIANT varChild, BSTR *pszHelp);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
protected:
	// ���ݵ�ǰ״̬��ʼ��TrayMenu
	// �˺�������ÿ��Ӧ�ó���������״̬�л�ʱ����
	void UpdateUIStateByModel();

	// ���ݵ�ǰģʽ������ͼ��
	void AdjustModelIcon();
private:
	// ���ػ�����ʾ������
	void ShowMainUI();
	void HideMainUI(BOOL autoSwitchCheck = TRUE);
	bool ShowOverTimeMsgBox();
	BOOL isShown() const { return m_bShown;}

	// �Ի���
	CDlgCheckPassword m_dlgCheckPassword_;
	CDlgChangePassword m_dlgChangePassword_;
	CDlgImageBrowser m_dlgImageBrowser_;
	CDlgSearchWordList m_dlgSearchKeyword_;
	CDlgWebsites m_dlgWebsites_;
	CDlgSwitchChildren m_dlgSwitchChildren_;
	CDlgRegister m_dlgRegister_;

private:
	void OnRequestShowMainUI();		// ���û�Ҫ��ִ����ʾ�Ի���ʱ������
	void SwitchOnClose();
	void ShowRegTipDlg();

	// Tooltip���
	CTrayIconPosition m_tray_pos;
	CPPToolTip m_traytip;
	DWORD dwAppearLastTime_;
};
