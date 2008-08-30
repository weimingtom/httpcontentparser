// DlgScreenSaver.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgScreenSaver.h"


// CDlgScreenSaver 对话框

IMPLEMENT_DYNAMIC(CDlgScreenSaver, CDialog)
CDlgScreenSaver::CDlgScreenSaver(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgScreenSaver::IDD, pParent)
{
}

CDlgScreenSaver::~CDlgScreenSaver()
{
}

void CDlgScreenSaver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_FUNCTION, m_staFunction);
	DDX_Control(pDX, IDC_STA_TIMESPAN, m_staTimespan);
	DDX_Control(pDX, IDC_STA_AUTOCLEAR, m_staAutoClear);
}

void CDlgScreenSaver::OnApply() {
}
void CDlgScreenSaver::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgScreenSaver, CDialog)
END_MESSAGE_MAP()


// CDlgScreenSaver 消息处理程序
