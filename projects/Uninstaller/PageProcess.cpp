// PageProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "PageProcess.h"


// CPageProcess �Ի���

IMPLEMENT_DYNAMIC(CPageProcess, CPropertyPage)
CPageProcess::CPageProcess()
	: CPropertyPage(CPageProcess::IDD)
{
}

CPageProcess::~CPageProcess()
{
}

void CPageProcess::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageProcess, CPropertyPage)
END_MESSAGE_MAP()


// CPageProcess ��Ϣ�������
