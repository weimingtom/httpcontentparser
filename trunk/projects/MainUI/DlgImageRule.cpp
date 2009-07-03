// DlgImageRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgImageRule.h"
#include ".\globalvariable.h"
#include ".\dlgimagerule.h"
#include <utility\HTTPPacket.h>
#include <webcontenttype.h>
#include <typeconvert.h>
#include <comdef.h>
#include <logger\logger.h>

// CDlgImageRule �Ի���

IMPLEMENT_DYNAMIC(CDlgImageRule, CDialog)
CDlgImageRule::CDlgImageRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgImageRule::IDD, pParent)
	, m_bCheckGIF(FALSE)
	, m_bCheckJPEG(FALSE)
	, m_bCheckBMP(FALSE)
	, m_bCheckPNG(FALSE)
	, scope_min_(0)
	, scope_max_(0)
{
	// auther_name_ = ANOTHER_;
}

CDlgImageRule::~CDlgImageRule()
{
}

std::string CDlgImageRule::getHelpLink() const {
	return "";
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
	DDX_Check(pDX, IDC_CHK_GIF, m_bCheckGIF);
	DDX_Check(pDX, IDC_CHK_JPEG, m_bCheckJPEG);
	DDX_Check(pDX, IDC_CHK_BMP, m_bCheckBMP);
	DDX_Check(pDX, IDC_CHK_PNG, m_bCheckPNG);
	DDX_Control(pDX, IDC_SLIDER_IMAGECHECK_DEGREE, m_sliderImageCheckDegree);
	DDX_Control(pDX, IDC_SPIN_MIN, m_spinBtnMin);
	DDX_Control(pDX, IDC_SPIN_MAX, m_spinBtnMax);
	DDX_Control(pDX, IDC_EDIT_SCOPE_MIN, m_editMin);
	DDX_Control(pDX, IDC_EDIT_SCOPE_MAX, m_editMax);
	DDX_Control(pDX, IDC_CHK_ENABLE_SIZE_CHECK, m_chkEnableScopeCheck);
	DDX_Text(pDX, IDC_EDIT_SCOPE_MIN, scope_min_);
	DDX_Text(pDX, IDC_EDIT_SCOPE_MAX, scope_max_);
}

void CDlgImageRule::OnShow() {
}

int CDlgImageRule::OnApply() {
	UpdateData(TRUE);
	// �����ڼ�¼������
	//g_configuration.getContentCheckSetting()->enableCheck(IMAGE_TYPE_GIF, m_bCheckGIF);
	//g_configuration.getContentCheckSetting()->enableCheck(IMAGE_TYPE_JPEG, m_bCheckJPEG);
	//g_configuration.getContentCheckSetting()->enableCheck(IMAGE_TYPE_BMP, m_bCheckBMP);
	//g_configuration.getContentCheckSetting()->enableCheck(IMAGE_TYPE_PNG, m_bCheckPNG);
	//g_configuration.getContentCheckSetting()->setImageCheckTightness(m_sliderImageCheckDegree.GetPos());
	//g_configuration.getContentCheckSetting()->enableCheckBySize(m_chkEnableScopeCheck.GetCheck() == BST_CHECKED);

	//g_configuration.getContentCheckSetting()->setCheckScope(scope_min_, scope_max_);

	// apply to COM Services
	try {
		IWebContentCheck *contentCheck = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebContentCheck, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentCheck, (LPVOID*)&contentCheck);
		if (FAILED(hr)) {
			__LERR__("Create Webcontent failed with HRESULT vlaue"<<hr);
			return -1;
		}

		contentCheck->setCheckScope(scope_min_, scope_max_);
		contentCheck->enableCheck(convert(m_bCheckGIF),  IMAGE_TYPE_GIF);
		contentCheck->enableCheck(convert(m_bCheckJPEG), IMAGE_TYPE_JPEG);
		contentCheck->enableCheck(convert(m_bCheckBMP),  IMAGE_TYPE_BMP);
		contentCheck->enableCheck(convert(m_bCheckPNG),  IMAGE_TYPE_PNG);
		contentCheck->put_ImageCheckTightness(m_sliderImageCheckDegree.GetPos());
	} catch (_com_error& e) {
		__LERR__("_com_error exception with Description : "<<  (TCHAR*)e.Description());
	} catch (...) {
		__LERR__("CATCH(...)");
	}
	
	return 0;
}

// ���е����ö���������Confiruation�У� ��Ϊ
// ÿ�λָ��Ƕ�Ӧ����������ж�ȡ����
// ����������������ʱ���ǲ��Եģ���˶Ժ��ܹ���OnShow�У���
// COM Service����ȡ�����ݣ�Ȼ������ʵ
void CDlgImageRule::restoreSetting() {
	// ���ճ�ʼ������
	//m_bCheckGIF = g_configuration.getContentCheckSetting()->isSettingNeedCheck(IMAGE_TYPE_GIF);
	//m_bCheckJPEG = g_configuration.getContentCheckSetting()->isSettingNeedCheck(IMAGE_TYPE_JPEG);
	//m_bCheckBMP = g_configuration.getContentCheckSetting()->isSettingNeedCheck(IMAGE_TYPE_BMP);
	//m_bCheckPNG = g_configuration.getContentCheckSetting()->isSettingNeedCheck(IMAGE_TYPE_PNG);

	m_sliderImageCheckDegree.SetRange(0, 4);
	//m_sliderImageCheckDegree.SetPos(g_configuration.getContentCheckSetting()->getImageCheckTightness());

	// �Ƿ�������ݴ�С���м��
	bool enabed_check_by_size = true;// g_configuration.getContentCheckSetting()->enabledCheckBySize();
	enableScopeCheck(enabed_check_by_size);
	m_chkEnableScopeCheck.SetCheck(enabed_check_by_size ? BST_CHECKED : BST_UNCHECKED);

	// ȡ�ü�鷶Χ
	//g_configuration.getContentCheckSetting()->getCheckedScope(&scope_min_, &scope_max_);
	
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CDlgImageRule, CDialog)
	ON_BN_CLICKED(IDC_CHK_JPEG, OnBnClickedChkJpeg)
	ON_BN_CLICKED(IDC_CHK_GIF, OnBnClickedChkGif)
	ON_BN_CLICKED(IDC_CHK_BMP, OnBnClickedChkBmp)
	ON_BN_CLICKED(IDC_CHK_PNG, OnBnClickedChkPng)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CHK_ENABLE_SIZE_CHECK, OnBnClickedChkEnableSizeCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgImageRule ��Ϣ�������

BOOL CDlgImageRule::OnInitDialog() 
{
	CBaseDlg::OnInitDialog();
	Restore();
	return TRUE;
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


void CDlgImageRule::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_sliderImageCheckDegree.GetSafeHwnd()) {
		SetModify(true);
	}
	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgImageRule::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_spinBtnMin.GetSafeHwnd()) {
		SetModify(true);
	} else 	if (pScrollBar->GetSafeHwnd() == m_spinBtnMax.GetSafeHwnd()) {
		SetModify(true);
	}
	CBaseDlg::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDlgImageRule::OnBnClickedChkEnableSizeCheck()
{
	SetModify(true);

	bool enabled = m_chkEnableScopeCheck.GetCheck() == BST_CHECKED ? true : false;
	enableScopeCheck(enabled);
}

void CDlgImageRule::enableScopeCheck(bool enabled) {
	m_editMin.EnableWindow(enabled);
	m_editMax.EnableWindow(enabled);
	m_spinBtnMax.EnableWindow(enabled);
	m_spinBtnMin.EnableWindow(enabled);
}

BOOL CDlgImageRule::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (m_editMin.GetSafeHwnd() == pMsg->hwnd||
			m_editMax.GetSafeHwnd() == pMsg->hwnd) {
				SetModify(true);
			}	
	}
	return CBaseDlg::PreTranslateMessage(pMsg);
}

HBRUSH CDlgImageRule::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
