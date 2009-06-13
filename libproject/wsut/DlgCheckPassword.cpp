// DlgCheckPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "wsut.h"
#include "DlgCheckPassword.h"


// CDlgCheckPassword 对话框

IMPLEMENT_DYNAMIC(CDlgCheckPassword, CDialog)
CDlgCheckPassword::CDlgCheckPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckPassword::IDD, pParent)
{
}

CDlgCheckPassword::~CDlgCheckPassword()
{
}

void CDlgCheckPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCheckPassword, CDialog)
END_MESSAGE_MAP()


// CDlgCheckPassword 消息处理程序
