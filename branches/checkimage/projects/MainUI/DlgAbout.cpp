// DlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgAbout.h"

// CDlgAbout �Ի���

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)
CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgAbout::IDD, pParent)
{
}

CDlgAbout::~CDlgAbout()
{
}


int CDlgAbout::OnApply() {
	return 0;
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


// CDlgAbout ��Ϣ�������
