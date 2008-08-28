// DlgToolsSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgToolsSetting.h"
#include ".\dlgtoolssetting.h"


// CDlgToolsSetting 对话框

IMPLEMENT_DYNAMIC(CDlgToolsSetting, CDialog)
CDlgToolsSetting::CDlgToolsSetting(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgToolsSetting::IDD, pParent)
{
}

CDlgToolsSetting::~CDlgToolsSetting()
{
}

void CDlgToolsSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_IMAGE_SAVE, m_staScreenSaver);
	DDX_Control(pDX, IDC_STA_WEBCONTENT, m_staWebContent);
	DDX_Control(pDX, IDC_STA_PROGRAMHISTORY, m_staProgramHistory);
}


void CDlgToolsSetting::OnApply() {
}
void CDlgToolsSetting::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgToolsSetting, CDialog)
END_MESSAGE_MAP()


// CDlgToolsSetting 消息处理程序

BOOL CDlgToolsSetting::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}
