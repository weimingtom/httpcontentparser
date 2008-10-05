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

void CDlgOnlineHour::OnRestore() {

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
			for (int hour = 0; hour < 23; ++hour) {
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

void CDlgOnlineHour::OnApply() {
	try {
		CoInitialize(NULL);
		IAccessNetwork * accessNetwork = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AccessNetwork, NULL, CLSCTX_LOCAL_SERVER,
			IID_IAccessNetwork, (LPVOID*)&accessNetwork);

		Enumerator enumerate(accessNetwork);
		enumerate.reset();
		cells.StarEnum(&enumerate);

		accessNetwork->Release();
		CoUninitialize();
	} catch (_com_error &) {
		CoUninitialize();
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

void CDlgOnlineHour::initializeSetting() {
	m_bEnableTimeCheck = g_configuration.getOnlineSetting()->isEnabled();
	UpdateData(FALSE);

	// 
	g_configuration.getOnlineSetting()->enumBlockHour((Enumerator2<int, int>*)this);
}

int CDlgOnlineHour::Enum(const int day, const int hour) {
	cells.check(day, hour);
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
END_MESSAGE_MAP()


// CDlgOnlineHour 消息处理程序

BOOL CDlgOnlineHour::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_STA_CELLS)->GetWindowRect(rect);
	cells.Create(NULL, NULL, WS_CHILD, rect, this, IDC_WND_HELLO);
	cells.ShowWindow(SW_SHOW);

	initializeSetting();

	return TRUE;  // return TRUE unless you set the focus to a control
}

