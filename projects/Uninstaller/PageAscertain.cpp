// PageAscertain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "PageAscertain.h"


// CPageAscertain �Ի���

IMPLEMENT_DYNAMIC(CPageAscertain, CPropertyPage)
CPageAscertain::CPageAscertain()
	: CPropertyPage(CPageAscertain::IDD)
{
	GetDlgItem(ID_PREV_PANE)->EnableWindow(FALSE);
}

CPageAscertain::~CPageAscertain()
{
}

void CPageAscertain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageAscertain, CPropertyPage)
END_MESSAGE_MAP()


// CPageAscertain ��Ϣ�������
