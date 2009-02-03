// DlgWebsites.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgWebsites.h"
#include ".\dlgwebsites.h"


// CDlgWebsites �Ի���

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


// CDlgWebsites ��Ϣ�������

BOOL CDlgWebsites::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_list.InsertColumn(0, TEXT("address"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, TEXT("type"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, TEXT("visit count"), LVCFMT_LEFT, 90);

	// �Ƿ���Ҫ��ʾһ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ���ļ��ж�ȡ��ҳ���ݲ���ʾ��List����
void CDlgWebsites::initializeList() {
}