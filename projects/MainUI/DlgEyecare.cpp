// DlgEyecare.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgEyecare.h"
#include ".\dlgeyecare.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <comdef.h>
#include <logger_name.h>

#define ID_TIME_UPDATE_STATE  1010
#define TIME_ESCPLE			  500

// CDlgEyecare 对话框

IMPLEMENT_DYNAMIC(CDlgEyecare, CDialog)
CDlgEyecare::CDlgEyecare(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgEyecare::IDD, pParent)
	, m_nEnterTime(0)
	, m_nEyecareTime(0)
	, m_strCurrentState(_T(""))
	, m_strTimeLeft(_T(""))
{
	auther_name_ = ANOTHER_EP;
}

CDlgEyecare::~CDlgEyecare()
{
}

std::string CDlgEyecare::getHelpLink() const {
	return "";
}

void CDlgEyecare::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_EYECARE_TIME, m_staEyecare);
	DDX_Control(pDX, IDC_STA_STATE, m_staState);
	DDX_Control(pDX, IDC_EDT_ENTERTIME, m_edtEnterTime);
	DDX_Control(pDX, IDC_STA_AFTEREYECARE_TERMINATE, m_staAfterTerm);
	DDX_Control(pDX, IDC_EDT_RESTTIME, m_edtRestTime);
	DDX_Text(pDX, IDC_STA_CURRENT_STATE, m_strCurrentState);
	DDX_Text(pDX, IDC_EDT_ENTERTIME, m_nEnterTime);
	DDX_Text(pDX, IDC_EDT_RESTTIME, m_nEyecareTime);
	DDX_Text(pDX, IDC_STA_TIME_LEFT, m_strTimeLeft);
	DDX_Control(pDX, IDC_CHK_ENABLE_EYECARE, m_chkEnabled);
}

// 设置时间间隔
void CDlgEyecare::setEyecareTimespan() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		HRESULT hr =CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		pEyeCare->setEnterTime(m_nEnterTime * 60);
		pEyeCare->setEyecareTime(m_nEyecareTime * 60);
		pEyeCare->enableEyecare(convert(m_chkEnabled.GetCheck() == BST_CHECKED ? true : false));
		pEyeCare->Release();
	} catch (_com_error&) {
		LOG4CXX_ERROR(log4cxx::Logger::getLogger(MAINUI_LOGGER_ERROR), "CDlgEyecare::setEyecareTimespan::catch");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
	}
}

// 设置输入密码结束锁定后的模式
void CDlgEyecare::setEyecareTerminatedMode() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
		}

		UINT checked = GetCheckedRadioButton(IDC_RAD_ENTER_SU_MODE, IDC_RAD_JUST_RESET_TIMER);
		const int mode = (checked ==  IDC_RAD_ENTER_SU_MODE) ? 
			EyecareSetting::EYECARE_TERMIN_ENTERSU : EyecareSetting::EYECARE_TERMIN_RESETTIMER;

		pEyeCare->setTermMode(mode);
		pEyeCare->Release();
	} catch(...) {
		LOG4CXX_ERROR(log4cxx::Logger::getLogger(MAINUI_LOGGER_ERROR), "CDlgEyecare::setEyecareTerminatedMode::catch");
		throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}

int CDlgEyecare::OnApply() {
	setEyecareTimespan();
	setEyecareTerminatedMode();
	
	UINT checked = GetCheckedRadioButton(IDC_RAD_ENTER_SU_MODE, IDC_RAD_JUST_RESET_TIMER);
	const int mode = (checked ==  IDC_RAD_ENTER_SU_MODE) ? 
			EyecareSetting::EYECARE_TERMIN_ENTERSU : EyecareSetting::EYECARE_TERMIN_RESETTIMER;

	return 0;
}

void CDlgEyecare::OnShow() {
}

void CDlgEyecare::restoreSetting() {
	try {
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		pEyeCare->getEnterTime((LONG*)&m_nEnterTime);
		pEyeCare->getEyecareTime((LONG*)&m_nEyecareTime);

		// 读出出示信息, 时间单位不同， 存储单位是sec, 而显示单位是min
		m_nEnterTime /= 60;
		m_nEyecareTime /= 60;

		LONG mode;
		pEyeCare->getTermMode(&mode);
		assert(mode == EyecareSetting::EYECARE_TERMIN_ENTERSU || mode == EyecareSetting::EYECARE_TERMIN_RESETTIMER);
		
		UINT checked = (mode == EyecareSetting::EYECARE_TERMIN_RESETTIMER) ? IDC_RAD_JUST_RESET_TIMER : IDC_RAD_ENTER_SU_MODE;
		CheckRadioButton(IDC_RAD_ENTER_SU_MODE, IDC_RAD_JUST_RESET_TIMER, checked);

		VARIANT_BOOL setting_enabled;
		pEyeCare->isSettingEnabled(&setting_enabled);
		UINT enabled = convert(setting_enabled)? BST_CHECKED : BST_UNCHECKED;
		m_chkEnabled.SetCheck(enabled);
		
		UpdateData(FALSE);

		pEyeCare->Release();
	} catch(...) {
		LOG4CXX_ERROR(log4cxx::Logger::getLogger(MAINUI_LOGGER_ERROR), "CDlgEyecare::restoreSetting::catch");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
	}
}

BEGIN_MESSAGE_MAP(CDlgEyecare, CDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RAD_JUST_RESET_TIMER, OnBnClickedRadJustResetTimer)
	ON_BN_CLICKED(IDC_RAD_ENTER_SU_MODE, OnBnClickedRadEnterSuMode)
	ON_EN_CHANGE(IDC_EDT_RESTTIME, OnEnChangeEdtResttime)
	ON_EN_CHANGE(IDC_EDT_ENTERTIME, OnEnChangeEdtEntertime)
	ON_BN_CLICKED(IDC_CHK_ENABLE_EYECARE, OnBnClickedEnableEyecare)
	ON_WM_VSCROLL()
	
END_MESSAGE_MAP()


// CDlgEyecare 消息处理程序
BOOL CDlgEyecare::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// 获取设置
	Restore();

	UpdateState();
	SetTimer(ID_TIME_UPDATE_STATE, TIME_ESCPLE, NULL);
	
	return TRUE;
}



void CDlgEyecare::UpdateState() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		HRESULT hr = CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		if (FAILED(hr)) {
			return ;
		}

		LONG value;
		pEyeCare->getState(&value);
		m_strCurrentState.LoadString(value == EyecareSetting::EYECARE_TIME ? IDS_EYECARE_STATE_EYECARE : IDS_EYECARE_STATE_ENTERTAIN);

		pEyeCare->getTimeLeft(&value);
		if (value > 60) {
			m_strTimeLeft.Format("%d mins.", value/60);
		} else {
			m_strTimeLeft.Format("%d sec..", value);
		}

		pEyeCare->Release();
		UpdateData(FALSE);
	} catch (...) {
		LOG4CXX_ERROR(log4cxx::Logger::getLogger(MAINUI_LOGGER_ERROR), "CDlgEyecare::UpdateState::catch");
	}
}
void CDlgEyecare::OnTimer(UINT nIDEvent) {
	if (nIDEvent == ID_TIME_UPDATE_STATE) {
		UpdateState();
	}
	CBaseDlg::OnTimer(nIDEvent);
}

void CDlgEyecare::OnDestroy() {
	CBaseDlg::OnDestroy();
	KillTimer(ID_TIME_UPDATE_STATE);
}


//=============================================
// 状态改变
void CDlgEyecare::OnBnClickedRadJustResetTimer()
{
	SetModify(true);
}

void CDlgEyecare::OnBnClickedRadEnterSuMode()
{
	SetModify(true);
}

void CDlgEyecare::OnEnChangeEdtResttime()
{
	SetModify(true);
}

void CDlgEyecare::OnEnChangeEdtEntertime()
{
	SetModify(true);
}

void CDlgEyecare::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SetModify(true);
}

void CDlgEyecare::OnBnClickedEnableEyecare()
{
	SetModify(true);
}
