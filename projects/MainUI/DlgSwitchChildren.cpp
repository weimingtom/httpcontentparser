// DlgSwitchChildren.cpp : implementation file
//

#include "stdafx.h"
#include ".\DlgSwitchChildren.h"
#include ".\resource.h"
#include ".\globalvariable.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include <comdef.h>
#include <logger\logger.h>


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

	// ��ȡ����ʽ������Ѿ�ȷ�������Ҳ���Ҫ�ڵ����Ի���
	// ��ֱ�ӹرնԻ���

	try {
		AutoInitInScale auto_scale_;
		ISnowmanSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
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


void CDlgSwitchChildren::putParameterToCOM(const bool autoswitchOnClose) {
	// ��
	try {
		UpdateData(TRUE);
		AutoInitInScale auto_scale_;
		ISnowmanSetting * appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&appSetting);
		if (FAILED(hr)) {
			__LERR__("Create SnowmanSetting Failed with HRESULT value "<< hr);
			return OnOK();
		} else {
			appSetting->put_autoSwitchOnClose(autoswitchOnClose ? VARIANT_TRUE : VARIANT_FALSE);
			appSetting->put_askMeAgain(convert(!m_bDontAskmeAgain));	// �����෴
		}
	} catch (_com_error & e) {
		__LERR__("A exception catched  with description "<< e.Description());
	} catch(...) {
		__LERR__("Unknown exception ");
	}
}
void CDlgSwitchChildren::OnBnClickedOk()
{	
	putParameterToCOM(true);
	OnOK();
}


void CDlgSwitchChildren::OnBnClickedCancel()
{
	putParameterToCOM(false);
	OnCancel();
}
