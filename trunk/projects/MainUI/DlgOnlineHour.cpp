// DlgOnlineHour.cpp : ʵ���ļ�
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
#include <logger\logger.h>

// CDlgOnlineHour �Ի���
IMPLEMENT_DYNAMIC(CDlgOnlineHour, CDialog)
CDlgOnlineHour::CDlgOnlineHour(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOnlineHour::IDD, pParent)
	, m_bEnableTimeCheck(FALSE)
{
	auther_name_ = ANOTHER_IT;
}

CDlgOnlineHour::~CDlgOnlineHour()
{
}

std::string CDlgOnlineHour::getHelpLink() const {
	return "";
}

namespace {
	// ����
class Enumerator : public Enumerator2<INT_PTR, INT_PTR> {
public:
	Enumerator(IAccessNetwork * access) {
		accessNetwork_ = access;
		assert (accessNetwork_ != NULL);
	}

	// ȡ�����е�����
	void reset() {
		for (INT_PTR day = 0; day < 7; ++day) {
			for (INT_PTR hour = 0; hour < 24; ++hour) {
				accessNetwork_->removeBlockTime(day, hour);
			}
		}
	}
	virtual INT_PTR Enum(const INT_PTR day, const INT_PTR hour) {
		accessNetwork_->setBlockTime(day, hour);
		return 0;
	}

private:
	IAccessNetwork * accessNetwork_;
};
}; // namespace

INT_PTR CDlgOnlineHour::OnApply() {
	try {
		AutoInitInScale _auto;

		IAccessNetwork * accessNetwork = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER,
			IID_IAccessNetwork, (LPVOID*)&accessNetwork);
		if (FAILED(hr)) {
			__LERR__("Create AccessNetwork with HRESULT vaue : "<<std::hex<<hr);
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}

		Enumerator enumerate(accessNetwork);
		enumerate.reset();
		cells.StarEnum(&enumerate);

		accessNetwork->Release();
		return 0;
	} catch (_com_error & e) {
		__LERR__("_com_error exception with description : "<<(TCHAR*)e.Description());
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
			__LERR__("Create AccessNetwork with HRESULT value "<<std::hex<<hr);
			throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
		}

		VARIANT_BOOL isSettingEnabled;
		for (INT_PTR day = 0; day < 7; ++day) {
			for (INT_PTR hour = 0; hour < 24; ++hour) {
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
		__LERR__("CATCH(...)");
		throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}

BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
	ON_BN_CLICKED(IDC_CHK_TIMECTRL, OnBnClickedChkTimectrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgOnlineHour ��Ϣ�������

BOOL CDlgOnlineHour::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_STA_CELLS)->GetWindowRect(rect);
	ScreenToClient(&rect);
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

HBRUSH CDlgOnlineHour::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
