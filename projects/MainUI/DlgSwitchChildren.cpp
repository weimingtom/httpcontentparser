// DlgSwitchChildren.cpp : implementation file
//

#include "stdafx.h"
#include ".\DlgSwitchChildren.h"
#include ".\resource.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>

// CDlgSwitchChildren dialog

IMPLEMENT_DYNAMIC(CDlgSwitchChildren, CPopupDialog)

CDlgSwitchChildren::CDlgSwitchChildren(CWnd* pParent /*=NULL*/)
	: CPopupDialog(CDlgSwitchChildren::IDD, pParent)
	, m_bDontAskmeAgain(FALSE)
{

}

CDlgSwitchChildren::~CDlgSwitchChildren()
{
}

void CDlgSwitchChildren::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_DONT_ASKME_AGAIN, m_bDontAskmeAgain);
}


BEGIN_MESSAGE_MAP(CDlgSwitchChildren, CPopupDialog)
	ON_BN_CLICKED(IDOK, &CDlgSwitchChildren::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSwitchChildren::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSwitchChildren message handlers
BOOL CDlgSwitchChildren::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 获取处理方式，如果已经确定，而且不需要在弹出对话框
	// 则直接关闭对话框

	try {
		AutoInitInScale auto_scale_;
		IAppSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		if (SUCCEEDED(hr)) {
			VARIANT_BOOL askme, closed;
			appSetting->get_askMeAgain(&askme);
			appSetting->get_autoSwitchOnClose(&closed);

			if (VARIANT_FALSE == askme) {
				if (VARIANT_FALSE == closed) {
					EndDialog(IDCANCEL);
				} else {
					EndDialog(IDOK);
				}
			}
		}
	} catch (...) {
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgSwitchChildren::OnBnClickedOk()
{
	// 首
	try {
		UpdateData(TRUE);
		AutoInitInScale auto_scale_;
		IAppSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			return OnOK();
		} else {
			appSetting->put_autoSwitchOnClose(VARIANT_TRUE);
			appSetting->put_askMeAgain(convert(!m_bDontAskmeAgain));	// 正好相反
		}
	} catch (...) {
	}
	OnOK();
}


void CDlgSwitchChildren::OnBnClickedCancel()
{
		// 首
	try {
		UpdateData(TRUE);
		AutoInitInScale auto_scale_;
		IAppSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			return OnOK();
		} else {
			appSetting->put_autoSwitchOnClose(VARIANT_FALSE);
			appSetting->put_askMeAgain(convert(!m_bDontAskmeAgain));
		}
	} catch (...) {
	}
	OnCancel();
}
