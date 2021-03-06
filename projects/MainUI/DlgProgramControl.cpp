// DlgProgramControl.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"
#include ".\globalvariable.h"
#include <apputility\apputility.h>
#include <apputility\fileinfo.h>
#include <comdef.h>
#include <com\comutility.h>
#include <com\resultvalue.h>
#include <typeconvert.h>
#include <logger\logger.h>

// CDlgProgramControl 对话框

const CString CProgramList::GetToolTip(INT_PTR nItem, INT_PTR nSubItem, UINT nFlags, BOOL&) {
	return "";
}

IMPLEMENT_DYNAMIC(CDlgProgramControl, CDialog)
CDlgProgramControl::CDlgProgramControl(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgProgramControl::IDD, pParent)
, m_bEnableAppControl(FALSE)
{
	auther_name_ = ANOTHER_AC;
}

CDlgProgramControl::~CDlgProgramControl() {
	resetContent();
}

std::string CDlgProgramControl::getHelpLink() const {
	return "";
}

void CDlgProgramControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_list);
	DDX_Check(pDX, IDC_CHK_ENABLE_APPCONTROL, m_bEnableAppControl);
}

void CDlgProgramControl::addItem(const std::string &filepath, const INT_PTR iIndex) {
	addedItems_.insert(std::make_pair(filepath, iIndex));
	
	// 从删除列表中删除
	MODIFY_ITEMS::iterator iter = deleteItems_.find(filepath);
	if (iter != deleteItems_.end()) {
		deleteItems_.erase(iter);
	}
}

void CDlgProgramControl::deleteItem(const std::string &filepath, const INT_PTR nItem) {
	deleteItems_.insert(std::make_pair(filepath, nItem));

	// 从添加列表中删除
	MODIFY_ITEMS::iterator iter = addedItems_.find(filepath);
	if (iter != addedItems_.end()) {
		addedItems_.erase(iter);
	}
}


void CDlgProgramControl::removeItemData(const CString &path) {
	DATA_MAP::iterator eraserIter = listdata_.find((LPCTSTR)path);
	if (listdata_.end() != eraserIter) {
		delete eraserIter->second;
		listdata_.erase(eraserIter);
	}
}

// 执行删除的过程
void CDlgProgramControl::executeDelete(IAppControl *pSetting) {
	MODIFY_ITEMS::iterator iter = deleteItems_.begin();
	for (; iter != deleteItems_.end(); ++iter) {
		// 从COM服务中删除
		pSetting->RemoveItem((BSTR)_bstr_t(iter->first.c_str()));
	}

	deleteItems_.clear();
}

// 执行添加的过程
void CDlgProgramControl::executeAdd(IAppControl *pSetting) {
	// 将新增的项加入进去
	MODIFY_ITEMS::iterator iter = addedItems_.begin();
	for (; iter != addedItems_.end(); ++iter) {
		pSetting->AddNewItem((BSTR)_bstr_t(iter->first.c_str()));
	}
	addedItems_.clear();
}

void CDlgProgramControl::resetContent() {
	// 冲值修改项
	addedItems_.clear();
	deleteItems_.clear();

	DATA_MAP::iterator iter = listdata_.begin();
	for (; iter != listdata_.end(); ++iter) {
		if (NULL != iter->second) {
			delete iter->second;
		}
	}
	listdata_.clear();
}

INT_PTR CDlgProgramControl::OnApply() {
	try {
		UpdateData(TRUE);
		AutoInitInScale _auto;

		IAppControl *pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&pSetting);
		if (FAILED(hr) || NULL == pSetting) {
			__LERR__("Create AppControl failed with HRESULT value " <<std::hex<<hr);
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return 0;
		}

		// 执行添加删除操作
		executeAdd(pSetting);
		executeDelete(pSetting);
		pSetting->enable(convert(m_bEnableAppControl));

		pSetting->Release();
		pSetting = NULL;

		return SUCCESS_APPLY;
	} catch (_com_error &e) {
		__LERR__("_com_error excpetion with Description : "<<(TCHAR*)e.Description());
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	} catch (...) {
		__LERR__("CATCH(...)");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}
}
void CDlgProgramControl::OnShow() {

}
void CDlgProgramControl::restoreSetting() {
	try {
		AutoInitInScale _auto;

		// 从COM服务器上获取数据
		IAppControl *pSetting;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			__LERR__("Create AppControl failed with HRESULT value "<<std::hex<<hr);
			throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
		}
	
		// 清空内容
		resetContent();
		m_list.DeleteAllItems();

		BSTR cur, next;
		LONG result;
		pSetting->GetFirstItem(&cur, &result);
		while (SeflComReturnValueSucc(result)) {
			CFileInfo fileinfo((TCHAR*)_bstr_t(cur));
			addNewFile(fileinfo);
			pSetting->GetNextItem(cur, &next, &result);

			//  cure不再使用
			SysFreeString(cur);
			cur = next;
		}

		// 是否可用
		VARIANT_BOOL enabled;
		pSetting->isSettingEnabled(&enabled);
		m_bEnableAppControl = convert(enabled);

		pSetting->Release();
		pSetting = NULL;
		UpdateData(FALSE);
	} catch (...) {
		__LERR__("CATCH(...)");
		throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}

INT_PTR CDlgProgramControl::addNewFile(const CFileInfo &info) {
	// 如果已经存在，则返回-1
 	if (listdata_.find(info.getFilePath()) != listdata_.end()) {
		return -1;
	}

	// 获取图标
	HICON hIcon = info.getICON();
	INT_PTR iconIndex = 1;
	if (hIcon != NULL) {
		iconIndex = m_imagelist.Add(hIcon);
	}


	// 设置文字信息
	// 如果无法获得任何信息， 则使用文件名称
	const TCHAR * displayName = NULL;
	if (info.getProductName().length() == 0) {
		TCHAR driver[10], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		_splitpath(info.getFilePath().c_str(), driver, dir, name, ext);
		displayName = name;
	} else {
		displayName = info.getProductName().c_str();
	}

	INT_PTR iItemIndex = iItemIndex = m_list.InsertItem(m_list.GetItemCount(), displayName, iconIndex);
	m_list.SetItemText(iItemIndex, 1, info.getFilePath().c_str());
	m_list.SetItemText(iItemIndex, 2, info.getCompanyName().c_str());
	m_list.SetItemText(iItemIndex, 3, info.getDescription().c_str());

	ITEMDATA *pData = new ITEMDATA(displayName, info.getCompanyName().c_str(), info.getDescription().c_str(), info.getFilePath().c_str());
	listdata_.insert(std::make_pair(info.getFilePath(), pData));
	m_list.SetItemData(iItemIndex, (DWORD_PTR)pData);

	return iItemIndex;
}

BEGIN_MESSAGE_MAP(CDlgProgramControl, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SET, OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_CHK_ENABLE_APPCONTROL, OnBnClickedChkEnableAppcontrol)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgProgramControl 消息处理程序
void CDlgProgramControl::OnBnClickedBtnAdd()
{
	// 打开文件
	TCHAR * FILE_FILTER = _T("Exectuable files(*.exe)|*.exe|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, FILE_FILTER);
	if (IDOK == dlg.DoModal()) {
		if (false == checkPath((LPCTSTR)dlg.GetPathName())) {
			AfxMessageBox(IDS_DLG_PROGRAM_PATH_IN_LIMITDIR, MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// 获取信息
		CFileInfo info((LPCTSTR)dlg.GetPathName());
		INT_PTR iIndex = addNewFile(info);
		if (iIndex < 0) {
			AfxMessageBox(IDS_DLG_PROGRAM_PATH_IN_LIMITDIR, MB_OK | MB_ICONEXCLAMATION);
		} else {
			addItem((LPCTSTR)dlg.GetPathName(), iIndex);
			SetModify(true);
		}
	}
}

void CDlgProgramControl::OnBnClickedBtnSet() {
}

BOOL CDlgProgramControl::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	// 初始化ImageList
	m_imagelist.Create(16, 16, ILC_COLOR32 | ILC_MASK, 50, 5);
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
		INT_PTR  nFormat;
		INT_PTR  nWidth;
	} colData[] =
	{
		{IDS_DLG_PROGRAM_CONTROL_NAME,			 LVCFMT_LEFT,  80}, 
		{IDS_DLG_PROGRAM_CONTROL_FULLPATH,		 LVCFMT_LEFT, 100},
		{IDS_DLG_PROGRAM_CONTROL_COMPANY,	 LVCFMT_LEFT, 90},
		{IDS_DLG_PROGRAM_CONTROL_DESCRIPT,		 LVCFMT_LEFT, 130},
	};
	const INT_PTR nColCount = sizeof colData / sizeof colData[0];

	CString str;
	for (INT_PTR nColumn = 0; nColumn < nColCount; ++nColumn)
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

	// 载入设置
	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgProgramControl::deleteJustFromUI(const INT_PTR nItem) {
	assert (-1 != nItem);
	// 将待删除的项保存起来，一边在用户按下Apply或者OK按钮时执行删除
	ITEMDATA * data = (ITEMDATA*)m_list.GetItemData(nItem);
	if (NULL != data) {
		deleteItem(data->fullPath, nItem);
		SetModify(true);

		// 从列表中删除
		removeItemData(data->fullPath.c_str());
	}
	m_list.DeleteItem(nItem);	// 从ListCtrl中删除当前想
}
void CDlgProgramControl::OnBnClickedBtnDel()
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos) {
		// 获取选中的项，
		INT_PTR nItem = m_list.GetNextSelectedItem(pos);
		if (nItem != -1) {
			deleteJustFromUI(nItem);
		}
	} 
}

void CDlgProgramControl::OnBnClickedChkEnableAppcontrol()
{
	SetModify(true);
}

HBRUSH CDlgProgramControl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}

//========================
// utility functions
bool CDlgProgramControl::checkPath(LPCTSTR lpstrFilepath) {
	TCHAR limitpath[MAX_PATH], moduleFile[MAX_PATH];
	// 获取windows路径
	GetWindowsDirectory(limitpath, MAX_PATH);
	if (0 == _tcsnicmp(limitpath, lpstrFilepath, _tcslen(limitpath))) {
		return false;
	}

	// 获取软件安装路径
	GetModuleFileName(NULL, moduleFile, MAX_PATH);
	GetFileNameDir(moduleFile, limitpath, MAX_PATH);
	if (0 == _tcsnicmp(limitpath, lpstrFilepath, _tcslen(limitpath))) {
		return false;
	}

	return true;
}
