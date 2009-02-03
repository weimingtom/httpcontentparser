// DlgWebsites.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgWebsites.h"
#include ".\dlgwebsites.h"


// CDlgWebsites 对话框

IMPLEMENT_DYNAMIC(CDlgWebsites, CDialog)
CDlgWebsites::CDlgWebsites(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWebsites::IDD, pParent)
{
}

CDlgWebsites::~CDlgWebsites()
{
}

void CDlgWebsites::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDlgWebsites, CDialog)
END_MESSAGE_MAP()


// CDlgWebsites 消息处理程序

BOOL CDlgWebsites::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_list.InsertColumn(0, TEXT("address"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, TEXT("type"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, TEXT("visit count"), LVCFMT_LEFT, 90);

	// 是否需要显示一个

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 从文件中读取网页数据并显示在List当中
void CDlgWebsites::initializeList() {
}