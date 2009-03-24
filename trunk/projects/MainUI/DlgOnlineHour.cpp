// DlgOnlineHour.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgOnlineHour.h"
#include ".\basedlg.h"
#include ".\dlgonlinehour.h"
#include ".\resource.h"
#include ".\globalvariable.h"
#include <comdef.h>
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>


// CDlgOnlineHour 对话框
IMPLEMENT_DYNAMIC(CDlgOnlineHour, CDialog)
CDlgOnlineHour::CDlgOnlineHour(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOnlineHour::IDD, pParent)
	, m_bEnableTimeCheck(FALSE)
{
}

CDlgOnlineHour::~CDlgOnlineHour()
{
}


namespace {
	// 设置
class Enumerator : public Enumerator2<int, int> {
public:
	Enumerator(IAccessNetwork * access) {
		accessNetwork_ = access;
		assert (accessNetwork_ != NULL);
	}

	// 取消已有的设置
	void reset() {
		for (int day = 0; day < 7; ++day) {
			for (int hour = 0; hour < 24; ++hour) {
				accessNetwork_->removeBlockTime(day, hour);
			}
		}
	}
	virtual int Enum(const int day, const int hour) {
		accessNetwork_->setBlockTime(day, hour);
		return 0;
	}

private:
	IAccessNetwork * accessNetwork_;
};
}; // namespace

int CDlgOnlineHour::OnApply() {
	try {
		AutoInitInScale _auto;

		IAccessNetwork * accessNetwork = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER,
			IID_IAccessNetwork, (LPVOID*)&accessNetwork);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}

		Enumerator enumerate(accessNetwork);
		enumerate.reset();
		cells.StarEnum(&enumerate);

		accessNetwork->Release();
		return 0;
	} catch (_com_error &) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return -1;
	}
}

void CDlgOnlineHour::OnShow() {
}

void CDlgOnlineHour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_TIMECTRL, m_chkTimeCtrl);
	DDX_Check(pDX, IDC_CHK_TIMECTRL, m_bEnableTimeCheck);
}

void CDlgOnlineHour::restoreSetting() {
	try {
		AutoInitInScale _auto;

		IAccessNetwork * accessNetwork = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER,
			IID_IAccessNetwork, (LPVOID*)&accessNetwork);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		VARIANT_BOOL isSettingEnabled;
		for (int day = 0; day < 7; ++day) {
			for (int hour = 0; hour < 24; ++hour) {
				hr = accessNetwork->SettingAccessNetwork(day, hour, &isSettingEnabled);
				if (false == convert(isSettingEnabled)) {
					cells.check(day, hour);
				}
			}
		}
	
		accessNetwork->isSettingEnable(&isSettingEnabled);
		m_bEnableTimeCheck = convert(isSettingEnabled);

		UpdateData(FALSE);
	} catch (...) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
	}
}

int CDlgOnlineHour::Enum(const int day, const int hour) {
	cells.check(day, hour);
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
	ON_BN_CLICKED(IDC_CHK_TIMECTRL, OnBnClickedChkTimectrl)
END_MESSAGE_MAP()


// CDlgOnlineHour 消息处理程序

BOOL CDlgOnlineHour::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_STA_CELLS)->GetWindowRect(rect);
	cells.setParentDlg(this);
	cells.Create(NULL, NULL, WS_CHILD, rect, this, IDC_WND_HELLO);
	cells.ShowWindow(SW_SHOW);

	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgOnlineHour::OnBnClickedChkTimectrl()
{
	SetModify(true);
}
