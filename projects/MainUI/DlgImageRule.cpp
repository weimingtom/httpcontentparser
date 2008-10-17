// DlgImageRule.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgImageRule.h"
#include ".\globalvariable.h"
#include ".\dlgimagerule.h"

#include <utility\HTTPPacket.h>
#include <webcontenttype.h>

// CDlgImageRule 对话框

IMPLEMENT_DYNAMIC(CDlgImageRule, CDialog)
CDlgImageRule::CDlgImageRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgImageRule::IDD, pParent)
	, m_bCheckGIF(FALSE)
	, m_bCheckJPEG(FALSE)
	, m_bCheckBMP(FALSE)
	, m_bCheckPNG(FALSE)
{
}

CDlgImageRule::~CDlgImageRule()
{
}

void CDlgImageRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_JPEG, m_chkJPEG);
	DDX_Control(pDX, IDC_CHK_GIF, m_chkGIF);
	DDX_Control(pDX, IDC_CHK_BMP, m_chkBMP);
	DDX_Control(pDX, IDC_CHK_PNG, m_chkPNG);
	DDX_Control(pDX, IDC_STA_IMAGE_CHECK, m_staImageCheck);
	DDX_Control(pDX, IDC_STA_IMAGETYPE, m_staImageType);
	DDX_Control(pDX, IDC_STA_IMAGESIZE, m_staImageSize);
	DDX_Control(pDX, IDC_EDIT2, m_editImageScale);
	DDX_Check(pDX, IDC_CHK_GIF, m_bCheckGIF);
	DDX_Check(pDX, IDC_CHK_JPEG, m_bCheckJPEG);
	DDX_Check(pDX, IDC_CHK_BMP, m_bCheckBMP);
	DDX_Check(pDX, IDC_CHK_PNG, m_bCheckPNG);
	DDX_Control(pDX, IDC_SLIDER_IMAGECHECK_DEGREE, m_sliderImageCheckDegree);
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


void CDlgImageRule::restoreSetting() {
	// 按照初始化设置
	m_bCheckGIF = g_configuration.getContentCheckSetting()->needCheck(IMAGE_TYPE_GIF);
	m_bCheckJPEG = g_configuration.getContentCheckSetting()->needCheck(IMAGE_TYPE_JPEG);
	m_bCheckBMP = g_configuration.getContentCheckSetting()->needCheck(IMAGE_TYPE_BMP);
	m_bCheckPNG = g_configuration.getContentCheckSetting()->needCheck(IMAGE_TYPE_PNG);
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CDlgImageRule, CDialog)
	ON_BN_CLICKED(IDC_CHK_JPEG, OnBnClickedChkJpeg)
	ON_BN_CLICKED(IDC_CHK_GIF, OnBnClickedChkGif)
	ON_BN_CLICKED(IDC_CHK_BMP, OnBnClickedChkBmp)
	ON_BN_CLICKED(IDC_CHK_PNG, OnBnClickedChkPng)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDlgImageRule 消息处理程序

BOOL CDlgImageRule::OnInitDialog() 
{
	CBaseDlg::OnInitDialog();
	m_sliderImageCheckDegree.SetRange(0, 5);
	m_editImageScale.SetMask("Low Bound:#### ---- ####:Upper Bound","Low Bound:____ ---- ____:Upper Bound",CGuiEdit::MASK_FREEMASK);
	Restore();
	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgImageRule::OnBnClickedChkJpeg()
{
	SetModify(true);
}

void CDlgImageRule::OnBnClickedChkGif()
{
	SetModify(true);
}

void CDlgImageRule::OnBnClickedChkBmp()
{
	SetModify(true);
}

void CDlgImageRule::OnBnClickedChkPng()
{
	SetModify(true);
}

void CDlgImageRule::OnEnChangeEdit2()
{
	SetModify(true);
}

void CDlgImageRule::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_sliderImageCheckDegree.GetSafeHwnd()) {
		SetModify(true);
	}
	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);
}
