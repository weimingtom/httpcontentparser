// DlgImageRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgImageRule.h"
#include "globalvariable.h"
#include <utility\HTTPPacket.h>

// CDlgImageRule 对话框

IMPLEMENT_DYNAMIC(CDlgImageRule, CDialog)
CDlgImageRule::CDlgImageRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgImageRule::IDD, pParent)
	, m_bShowImage(FALSE)
	, m_bCheckImage(FALSE)
{
}

CDlgImageRule::~CDlgImageRule()
{
}

void CDlgImageRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_IMAGE, m_chkImage);
	DDX_Control(pDX, IDC_CHK_SHOWIMAGE, m_chkShowImage);
	DDX_Control(pDX, IDC_CHK_JPEG, m_chkJPEG);
	DDX_Control(pDX, IDC_CHK_GIF, m_chkGIF);
	DDX_Control(pDX, IDC_CHK_BMP, m_chkBMP);
	DDX_Control(pDX, IDC_CHK_PNG, m_chkPNG);
	DDX_Check(pDX, IDC_CHK_SHOWIMAGE, m_bShowImage);
	DDX_Check(pDX, IDC_CHK_IMAGE, m_bCheckImage);
}

void CDlgImageRule::OnApply() {
	UpdateData(TRUE);

	ASSERT (g_globalChecker != NULL);

	g_globalChecker->enableShowImage(m_bShowImage == true ? VARIANT_TRUE : VARIANT_FALSE);

	g_globalChecker->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_GIF, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
	g_globalChecker->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_JPG, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
	g_globalChecker->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_PNG, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
}
BEGIN_MESSAGE_MAP(CDlgImageRule, CDialog)
END_MESSAGE_MAP()


// CDlgImageRule 消息处理程序
