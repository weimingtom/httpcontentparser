// DlgImageRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgImageRule.h"
#include "globalvariable.h"
#include <utility\HTTPPacket.h>
#include ".\dlgimagerule.h"

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
	DDX_Control(pDX, IDC_STA_IMAGE_CHECK, m_staImageCheck);
	DDX_Control(pDX, IDC_STA_IMAGETYPE, m_staImageType);
	DDX_Control(pDX, IDC_STA_IMAGESIZE, m_staImageSize);
	DDX_Control(pDX, IDC_EDIT2, m_editImageScale);
}

void CDlgImageRule::OnRestore() {

}

void CDlgImageRule::OnShow() {
}

void CDlgImageRule::OnApply() {
	UpdateData(TRUE);

	//ASSERT (g_globalSetting != NULL);

	//g_globalSetting->enableShowImage(m_bShowImage == true ? VARIANT_TRUE : VARIANT_FALSE);

	//g_dnssetting->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_GIF, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
	//g_dnssetting->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_JPG, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
	//g_dnssetting->enableImageCheck(HTTP_RESPONSE_HEADER::CONTYPE_PNG, m_bCheckImage == true ? VARIANT_TRUE : VARIANT_FALSE);
}
BEGIN_MESSAGE_MAP(CDlgImageRule, CDialog)
END_MESSAGE_MAP()


// CDlgImageRule 消息处理程序

BOOL CDlgImageRule::OnInitDialog() 
{
	CBaseDlg::OnInitDialog();
	
	m_chkImage.SetWindowText(" Check Image");
	m_chkShowImage.SetWindowText(" Show Image");
	m_editImageScale.SetMask("Low Bound:#### ---- ####:Upper Bound","Low Bound:____ ---- ____:Upper Bound",CGuiEdit::MASK_FREEMASK);
	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}
