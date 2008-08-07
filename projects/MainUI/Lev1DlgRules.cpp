// Lev1DlgRules.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "Lev1DlgRules.h"
#include ".\lev1dlgrules.h"


// CLev1DlgRules 对话框

IMPLEMENT_DYNAMIC(CLev1DlgRules, CDialog)
CLev1DlgRules::CLev1DlgRules(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CLev1DlgRules::IDD, pParent)
	, m_strComment(_T(""))
{
}

CLev1DlgRules::~CLev1DlgRules()
{
}

void CLev1DlgRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMENT, m_edit);
	DDX_Control(pDX, IDC_STA_COMMENT, m_staComment);
}


BEGIN_MESSAGE_MAP(CLev1DlgRules, CDialog)
END_MESSAGE_MAP()

void CLev1DlgRules::OnApply() {
}

void CLev1DlgRules::OnShow() {
}

// CLev1DlgRules 消息处理程序

BOOL CLev1DlgRules::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	
	CString strDNS, strImage, strText;
	strDNS.LoadString(IDS_COMMENT_DNS);
	strImage.LoadString(IDS_COMMENT_IMAGE);
	strText.LoadString(IDS_COMMENT_TEXT);
	m_strComment = "\n";
	m_strComment += strDNS;
	m_strComment += strImage;
	m_strComment += strText;

	m_edit.SetWindowText(m_strComment);

	return TRUE; 
}
