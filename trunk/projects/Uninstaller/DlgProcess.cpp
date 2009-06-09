// DlgProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "DlgProcess.h"
#include ".\dlgprocess.h"


// CDlgProcess 对话框

IMPLEMENT_DYNAMIC(CDlgProcess, CDialog)
CDlgProcess::CDlgProcess(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProcess::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgProcess::~CDlgProcess()
{
}

void CDlgProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_process);
}


BEGIN_MESSAGE_MAP(CDlgProcess, CDialog)
END_MESSAGE_MAP()


// CDlgProcess 消息处理程序

BOOL CDlgProcess::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  
}

void CDlgProcess::process() {
		// 处理消息
	m_process.SetPos(0);

	// 删除快捷方式
	m_process.SetPos(70);
	Sleep(100);

	// 设置启动项

	m_process.SetPos(100);
	Sleep(500);

	EndDialog(IDOK);
	Sleep(1000);
}