// DlgProgramControl.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"
#include ".\globalvariable.h"
#include <fileinfo.h>
#include <comdef.h>
#include <com\comutility.h>

// CDlgProgramControl 对话框

const CString CProgramList::GetToolTip(int nItem, int nSubItem, UINT nFlags, BOOL&) {
	CDlgProgramControl::ITEMDATA * data  = (CDlgProgramControl::ITEMDATA*)this->GetItemData(nItem);
	ASSERT(NULL != data);
	CString name, companyName, description, fullPath;
	name.Format("Product Name : %s\n", data->ProductName.c_str() );
	companyName.Format(data->CompanyName.length() != 0 ?"Company Name : %s\n", data->CompanyName.c_str() : "");
	description.Format(data->Description.length() != 0 ? "Descripton : %s\n", data->Description.c_str() : "");
	fullPath.Format("Path : %s\n", data->fullPath.c_str() );
	return "";
}

IMPLEMENT_DYNAMIC(CDlgProgramControl, CDialog)
CDlgProgramControl::CDlgProgramControl(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgProgramControl::IDD, pParent)
{
}

CDlgProgramControl::~CDlgProgramControl() {
	DATA_MAP::iterator iter = listdata_.begin();
	for (; iter != listdata_.end(); ++iter) {
		if (NULL != iter->second) {
			delete iter->second;
		}
	}
}

void CDlgProgramControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_list);
}

int CDlgProgramControl::OnApply() {
	try {
		AutoInitInScale _auto;

		IProgramControlSetting *pSetting;
		HRESULT hr = CoCreateInstance(CLSID_ProgramControlSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IProgramControlSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			// TODO: add information
			return 0;
		}

		// 将新增的项加入进去
		MODIFY_ITEMS::iterator iter = addedItems_.begin();
		for (; iter != addedItems_.end(); ++iter) {
			pSetting->AddNewItem((BSTR)_bstr_t(iter->c_str()));
		}
	} catch (_com_error &)
	{
	}
	return -1;
}
void CDlgProgramControl::OnShow() {

}
void CDlgProgramControl::restoreSetting() {
	try {
		AutoInitInScale _auto;

		// 从COM服务器上获取数据
		IProgramControlSetting *pSetting;
		HRESULT hr = CoCreateInstance(CLSID_ProgramControlSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IProgramControlSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			// TODO: add information
			return ;
		}

		_bstr_t cur, next;
		pSetting->GetFirstItem((BSTR*)&cur);
		while (cur.length() != 0) {
			addNewFile((TCHAR*)_bstr_t(cur));
			pSetting->GetNextItem((BSTR)cur, (BSTR*)&next);
			cur = next;
		}

		// 冲值修改项
		addedItems_.clear();
		deleteItems_.clear();
	} catch (_com_error &) {
	}
}

int CDlgProgramControl::addNewFile(const CString &fullpath) {
	// 如果已经存在，则返回-1
	if (listdata_.find((LPCTSTR)fullpath) != listdata_.end()) {
		return -1;
	}

	// 获取信息
	CFileInfo info((LPCTSTR)fullpath);

	// 获取图标
	HICON hIcon = info.getICON();
	int iconIndex = 1;
	if (hIcon != NULL) {
		iconIndex = m_imagelist.Add(hIcon);
	}


	// 设置文字信息
	// 如果无法获得任何信息， 则使用文件名称
	const TCHAR * displayName = NULL;
	if (info.getProductName().length() == 0) {
		TCHAR driver[10], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		_splitpath((LPCTSTR)fullpath, driver, dir, name, ext);
		displayName = name;
	} else {
		displayName = info.getProductName().c_str();
	}

	int iItemIndex = iItemIndex = m_list.InsertItem(m_list.GetItemCount(), displayName, iconIndex);
	m_list.SetItemText(iItemIndex, 1, info.getCompanyName().c_str());
	m_list.SetItemText(iItemIndex, 2, info.getDescription().c_str());
	m_list.SetItemText(iItemIndex, 3, fullpath);

	ITEMDATA *pData = new ITEMDATA(displayName, info.getCompanyName().c_str(), info.getDescription().c_str(), (LPCTSTR)fullpath);
	listdata_.insert(std::make_pair(fullpath, pData));
	m_list.SetItemData(iItemIndex, (DWORD_PTR)pData);

	addedItems_.insert((LPCTSTR)fullpath);
	return 0;
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
		if (0 != addNewFile(dlg.GetPathName())) {
			AfxMessageBox(IDS_DLG_PROGRAM_CONTROL_DUPLICATE_ITEM, MB_OK | MB_ICONEXCLAMATION);
		} else {
			SetModify(true);
		}
	}
}

void CDlgProgramControl::OnBnClickedBtnSet()
{
}

BOOL CDlgProgramControl::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// 初始化ImageList
	m_imagelist.Create(16, 16, ILC_COLOR24 | ILC_MASK, 50, 5);
	HICON hIcon;
	VERIFY(hIcon = AfxGetApp()->LoadIcon(IDI_DEFAULT));
	VERIFY(0 == m_imagelist.Add(hIcon));
	VERIFY(1 == m_imagelist.Add(hIcon));


	// 初始化listCtrl
	m_list.SetImageList(&m_imagelist, LVSIL_SMALL);
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
		{IDS_DLG_PROGRAM_CONTROL_NAME,			 LVCFMT_LEFT,  80}, 
		{IDS_DLG_PROGRAM_CONTROL_COMPANY,	 LVCFMT_LEFT, 90},
		{IDS_DLG_PROGRAM_CONTROL_DESCRIPT,		 LVCFMT_LEFT, 130},
		{IDS_DLG_PROGRAM_CONTROL_FULLPATH,		 LVCFMT_LEFT, 100},
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
