// DlgScreenSaver.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgScreenSaver.h"
#include "globalvariable.h"
#include ".\dlgscreensaver.h"

// CDlgScreenSaver 对话框

IMPLEMENT_DYNAMIC(CDlgScreenSaver, CDialog)
CDlgScreenSaver::CDlgScreenSaver(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgScreenSaver::IDD, pParent)
	, m_bEnableScreensave(FALSE)
	, m_bEnableAutoclean(FALSE)
{
}

CDlgScreenSaver::~CDlgScreenSaver()
{
}

void CDlgScreenSaver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_FUNCTION, m_staFunction);
	DDX_Control(pDX, IDC_STA_TIMESPAN, m_staTimespan);
	DDX_Control(pDX, IDC_STA_AUTOCLEAR, m_staAutoClear);
	DDX_Control(pDX, IDC_SLIDER_SAVE_TIMESPAN, m_sliderSaveTimespan);
	DDX_Control(pDX, IDC_SLIDER_CLEAN_TIMESPAN, m_sliderAutoclearTimespan);
	DDX_Check(pDX, IDC_CHK_SCREENSAVE, m_bEnableScreensave);
	DDX_Check(pDX, IDC_CHK_AUTOCLEAN, m_bEnableAutoclean);
}

void CDlgScreenSaver::OnRestore() {

}

void CDlgScreenSaver::OnApply() {
}
void CDlgScreenSaver::OnShow() {
}
 

void CDlgScreenSaver::initializeSetting() {
	m_sliderAutoclearTimespan.SetRangeMax(g_configuration.getScreenSaveAutoClean()->getRangeMax()/ ( 60 * 60 * 24));
	m_sliderAutoclearTimespan.SetRangeMin(g_configuration.getScreenSaveAutoClean()->getRangeMin()/ ( 60 * 60 * 24));
	m_sliderAutoclearTimespan.SetPos(g_configuration.getScreenSaveAutoClean()->getTimespan()/ (60 * 60 * 24));

	m_bEnableScreensave = g_configuration.getScreenSave()->isEnabled();
	m_bEnableAutoclean = g_configuration.getScreenSaveAutoClean()->isEnable();
}


void CDlgScreenSaver::enableAutoSave() {
	m_sliderSaveTimespan.EnableWindow(m_bEnableScreensave);
}
void CDlgScreenSaver::enableAutoclean() {
	m_sliderAutoclearTimespan.EnableWindow(m_bEnableAutoclean);
}

BEGIN_MESSAGE_MAP(CDlgScreenSaver, CDialog)
	ON_BN_CLICKED(IDC_CHK_SCREENSAVE, OnBnClickedChkScreensave)
	ON_BN_CLICKED(IDC_CHK_AUTOCLEAN, OnBnClickedChkAutoclean)
END_MESSAGE_MAP()


// CDlgScreenSaver 消息处理程序

BOOL CDlgScreenSaver::OnInitDialog() {
	CBaseDlg::OnInitDialog();
	
	initializeSetting();

	enableAutoSave();
	enableAutoclean();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgScreenSaver::OnBnClickedChkScreensave() {
	UpdateData(TRUE);
	enableAutoSave();
}

void CDlgScreenSaver::OnBnClickedChkAutoclean() {
	UpdateData(TRUE);
	enableAutoclean();
}
