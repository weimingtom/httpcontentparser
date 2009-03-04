// DlgProgramControl.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"
#include <fileinfo.h>

// CDlgProgramControl 对话框

IMPLEMENT_DYNAMIC(CDlgProgramControl, CDialog)
CDlgProgramControl::CDlgProgramControl(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgProgramControl::IDD, pParent)
{
}

CDlgProgramControl::~CDlgProgramControl()
{
}

void CDlgProgramControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_list);
}

int CDlgProgramControl::OnApply() {
	return -1;
}
void CDlgProgramControl::OnShow() {
}
void CDlgProgramControl::restoreSetting() {
}

void CDlgProgramControl::addNewFile(const CString &fullpath, const CString &filename) {
	CFileInfo info((LPCTSTR)fullpath);
	
	// 获取图标
	HICON hIcon = info.getICON();
	int iconIndex = 0;
	if (hIcon != NULL) {
		iconIndex = m_imagelist.Add(hIcon);
	}

	// 设置文字信息
	// 如果无法获得任何信息， 则使用文件名称
	int iItemIndex  = 0;
	if (info.getProductName().length() == 0) {
		iItemIndex = m_list.InsertItem(m_list.GetItemCount(), filename, iconIndex);
	} else {
		iItemIndex = m_list.InsertItem(m_list.GetItemCount(), info.getProductName().c_str(), iconIndex);
	}

	m_list.SetItemText(iItemIndex, 1, info.getCompanyName().c_str());
	m_list.SetItemText(iItemIndex, 2, info.getDescription().c_str());
}
BEGIN_MESSAGE_MAP(CDlgProgramControl, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SET, OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgProgramControl 消息处理程序

void CDlgProgramControl::OnBnClickedBtnAdd()
{
	// 打开文件
	TCHAR * FILE_FILTER = _T("Exectuable files(*.exe)|*.exe|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, FILE_FILTER);
	if (IDOK == dlg.DoModal()) {
		addNewFile(dlg.GetPathName(), dlg.GetFileName());
	}
}

void CDlgProgramControl::OnBnClickedBtnSet()
{
}

BOOL CDlgProgramControl::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// 初始化ImageList
	m_imagelist.Create(16, 16, ILC_COLOR24, 50, 10);
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_APPLICATION));


	// 初始化listCtrl
	m_list.SetImageList(&m_imagelist, LVSIL_STATE);
	m_list.SetExtendedStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP |
		LVS_EX_INFOTIP       | LVS_EX_LABELTIP);

	static const struct
	{
		UINT nColHdrId;
		int  nFormat;
		int  nWidth;
	} colData[] =
	{
		{IDS_DLG_PROGRAM_CONTROL_NAME,				  LVCFMT_LEFT,  80}, 
		{IDS_DLG_PROGRAM_CONTROL_COMPANY,	 LVCFMT_CENTER, 100},
		{IDS_DLG_PROGRAM_CONTROL_DESCRIPT,		  LVCFMT_RIGHT, 150},
	};
	const int nColCount = sizeof colData / sizeof colData[0];

	CString str;
	for (int nColumn = 0; nColumn < nColCount; ++nColumn)
	{
		VERIFY(str.LoadString(colData[nColumn].nColHdrId));
		m_list.InsertColumn(
			nColumn, str, colData[nColumn].nFormat, colData[nColumn].nWidth);
		if (nColumn > 0) m_list.EnableColumnHiding(nColumn, true);
	}
	

	m_list.EnableSortIcon  (TRUE, 1);
	m_list.ColorSortColumn (TRUE);
	m_list.KeepLabelLeft ();
	m_list.EnableSubItemTips  ();

	return TRUE;  // return TRUE unless you set the focus to a control
}
