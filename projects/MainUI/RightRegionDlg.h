#pragma once


// CRightRegionDlg 对话框
#include ".\basedlg.h"
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
#include ".\Lev1DlgRules.h"
#include ".\Lev1DlgTools.h"

class CRightRegionDlg : public CDialog
{
	DECLARE_DYNAMIC(CRightRegionDlg)

public:
	CRightRegionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRightRegionDlg();

// 对话框数据
	enum { IDD = IDD_DLG_RIGHTREGION };

public:
	int OnApplyChange();
	int OnCancelChange();
	int OnChangeDlgPage(const int itemdata);

	int initialize(CImageList	*m_pImageList, CDialog *pParent);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
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


	// 初始化对话框
	void initDlgs();	
	void setCurDlg(const DWORD item);
	void showDlg();
	void ChangeCurDlg(CBaseDlg *dlg);
	void setControlsFonts();

private:
	CFont	m_fontTitle;
	
private:
	void setRightTitle(const int item);
	void drawRightIcon(CDC *pDC);

	CImageList	*m_pImageList;			// 导航树上的图标
	CDialog * m_pParentDlg;

	WORD m_idIcon;
	WORD getItemIcon(DWORD itemData);
	WORD getItemIDS(DWORD itemData);
public:
	static const int SUCCESS_ON_APPLY = 0;
	static const int FAILED_ON_APPLY = -1;
};
