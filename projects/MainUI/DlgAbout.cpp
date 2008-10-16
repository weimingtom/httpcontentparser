// DlgAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgAbout.h"
#include <Guilib1.5\GuiGroupBox.h>

// CDlgAbout 对话框

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)
CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgAbout::IDD, pParent)
{
}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::OnRestore() {
}

void CDlgAbout::OnApply() {
}

void CDlgAbout::OnShow() {
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_ABOUT, m_staAbout);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
END_MESSAGE_MAP()


// CDlgAbout 消息处理程序
