// MainUIDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "dlgimagerule.h"
#include "dlgonlinehour.h"
#include "dlghelp.h"
#include "dlgabout.h"
#include "dlgdnsrule.h"
#include "dlgsearchrule.h"


// CMainUIDlg 对话框
class CMainUIDlg : public CDialog
{
// 构造
public:
	CMainUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAINUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl m_treeNavigation;
	void InitTreeNodes();		// 初始化树的节点
	CImageList m_imageList;
	void setCurDlg(const DWORD item);
	void initDlgs();
	void showDlg();
	// dlgs
	CDlgImageRule m_dlgImageRules;
	CDlgHelp	m_dlgHelp;
	CDlgOnlineHour m_dlgOnlineHour;
	CDlgSearchRule m_dlgSearchRule;
	CDlgDNSRule m_dlgDnsRule;
	CDlgAbout m_dlgAbout;
	CDialog	*m_curDlg;

	CRect    m_rectRight;
public:
	afx_msg void OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult);
};
