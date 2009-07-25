// DlgImageBrowser.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgImageBrowser.h"
#include ".\dlgimagebrowser.h"
#include <utility\strutility.h>
#include <apputility\apputility.h>
#include <vector>
#include <string>


// CDlgImageBrowser 对话框

IMPLEMENT_DYNAMIC(CDlgImageBrowser, CPopupDialog)
CDlgImageBrowser::CDlgImageBrowser(CWnd* pParent /*=NULL*/)
	: CPopupDialog(CDlgImageBrowser::IDD, pParent)
{
	m_ThumbCtrl = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TREE_SCREENSHOT);
}

CDlgImageBrowser::~CDlgImageBrowser()
{
}

void CDlgImageBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImageBrowser, CPopupDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDlgImageBrowser 消息处理程序

INT_PTR CDlgImageBrowser::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ThumbCtrl = new CThumbCtrl();
	m_ThumbCtrl->Create( WS_CHILD | WS_VISIBLE, CRect(0,0,256,148), this, 0x1004 );

	return 0;
}

BOOL CDlgImageBrowser::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect rect;
	GetDlgItem(IDC_IMAGES_POS)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_ThumbCtrl->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);

	initImageControl();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgImageBrowser::initImageControl() {
	ASSERT (m_ThumbCtrl != NULL);
	using namespace std;
	vector<strutility::_tstring> files;
	GetFilespathInDir((LPCTSTR)m_imageDir, "*.*", &files);

	INT_PTR cnt = 0;
	vector<strutility::_tstring>::iterator iter = files.begin();
	for (; iter != files.end(); ++iter) {
		if (strutility::endwith(iter->c_str(), ".jpg") || 
			strutility::endwith(iter->c_str(), ".gif") ||
			strutility::endwith(iter->c_str(), ".bmp") ||
			strutility::endwith(iter->c_str(), ".png")) {
			m_ThumbCtrl->InsertItem(cnt++, iter->c_str());
		}
	}
}
