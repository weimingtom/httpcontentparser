// DlgProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "DlgProcess.h"
#include ".\dlgprocess.h"


// CDlgProcess �Ի���

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


// CDlgProcess ��Ϣ�������

BOOL CDlgProcess::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  
}

void CDlgProcess::process() {
		// ������Ϣ
	m_process.SetPos(0);

	// ɾ����ݷ�ʽ
	m_process.SetPos(70);
	Sleep(100);

	// ����������

	m_process.SetPos(100);
	Sleep(500);

	EndDialog(IDOK);
	Sleep(1000);
}