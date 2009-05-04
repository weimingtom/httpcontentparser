// DlgProgramControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"
#include ".\globalvariable.h"
#include <fileinfo.h>
#include <comdef.h>
#include <com\comutility.h>
#include <com\resultvalue.h>
#include <typeconvert.h>

// CDlgProgramControl �Ի���

const CString CProgramList::GetToolTip(int nItem, int nSubItem, UINT nFlags, BOOL&) {
	return "";
}

IMPLEMENT_DYNAMIC(CDlgProgramControl, CDialog)
CDlgProgramControl::CDlgProgramControl(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgProgramControl::IDD, pParent)
, m_bEnableAppControl(FALSE)
{
}

CDlgProgramControl::~CDlgProgramControl() {
	resetContent();
}

void CDlgProgramControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_list);
	DDX_Check(pDX, IDC_CHK_ENABLE_APPCONTROL, m_bEnableAppControl);
}

void CDlgProgramControl::addItem(const std::string &filepath, const int iIndex) {
	addedItems_.insert(std::make_pair(filepath, iIndex));
	
	// ��ɾ���б���ɾ��
	MODIFY_ITEMS::iterator iter = deleteItems_.find(filepath);
	if (iter != deleteItems_.end()) {
		deleteItems_.erase(iter);
	}
}

void CDlgProgramControl::deleteItem(const std::string &filepath, const int nItem) {
	deleteItems_.insert(std::make_pair(filepath, nItem));

	// ������б���ɾ��
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

// ִ��ɾ���Ĺ���
void CDlgProgramControl::executeDelete(IAppControl *pSetting) {
	MODIFY_ITEMS::iterator iter = deleteItems_.begin();
	for (; iter != deleteItems_.end(); ++iter) {
		// ��COM������ɾ��
		pSetting->RemoveItem((BSTR)_bstr_t(iter->first.c_str()));
	}

	deleteItems_.clear();
}

// ִ����ӵĹ���
void CDlgProgramControl::executeAdd(IAppControl *pSetting) {
	// ��������������ȥ
	MODIFY_ITEMS::iterator iter = addedItems_.begin();
	for (; iter != addedItems_.end(); ++iter) {
		pSetting->AddNewItem((BSTR)_bstr_t(iter->first.c_str()));
	}
	addedItems_.clear();
}

void CDlgProgramControl::resetContent() {
	// ��ֵ�޸���
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

int CDlgProgramControl::OnApply() {
	try {
		UpdateData(TRUE);
		AutoInitInScale _auto;

		IAppControl *pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&pSetting);
		if (FAILED(hr) || NULL == pSetting) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return 0;
		}

		// ִ�����ɾ������
		executeAdd(pSetting);
		executeDelete(pSetting);
		pSetting->enable(convert(m_bEnableAppControl));

		pSetting->Release();
		pSetting = NULL;

		return SUCCESS_APPLY;
	} catch (_com_error &) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	} catch (...) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}
}
void CDlgProgramControl::OnShow() {

}
void CDlgProgramControl::restoreSetting() {
	try {
		AutoInitInScale _auto;

		// ��COM�������ϻ�ȡ����
		IAppControl *pSetting;
		HRESULT hr = CoCreateInstance(CLSID_AppControl, NULL, CLSCTX_LOCAL_SERVER, IID_IAppControl, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
		}
	
		// �������
		resetContent();
		m_list.DeleteAllItems();

		BSTR cur, next;
		LONG result;
		pSetting->GetFirstItem(&cur, &result);
		while (SeflComReturnValueSucc(result)) {
			CFileInfo fileinfo((TCHAR*)_bstr_t(cur));
			addNewFile(fileinfo);
			pSetting->GetNextItem(cur, &next, &result);

			//  cure����ʹ��
			SysFreeString(cur);
			cur = next;
		}

		// �Ƿ����
		VARIANT_BOOL enabled;
		pSetting->isSettingEnabled(&enabled);
		m_bEnableAppControl = convert(enabled);

		pSetting->Release();
		pSetting = NULL;
		UpdateData(FALSE);
	} catch (...) {
		throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}

int CDlgProgramControl::addNewFile(const CFileInfo &info) {
	// ����Ѿ����ڣ��򷵻�-1
 	if (listdata_.find(info.getFilePath()) != listdata_.end()) {
		return -1;
	}

	// ��ȡͼ��
	HICON hIcon = info.getICON();
	int iconIndex = 1;
	if (hIcon != NULL) {
		iconIndex = m_imagelist.Add(hIcon);
	}


	// ����������Ϣ
	// ����޷�����κ���Ϣ�� ��ʹ���ļ�����
	const TCHAR * displayName = NULL;
	if (info.getProductName().length() == 0) {
		TCHAR driver[10], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		_splitpath(info.getFilePath().c_str(), driver, dir, name, ext);
		displayName = name;
	} else {
		displayName = info.getProductName().c_str();
	}

	int iItemIndex = iItemIndex = m_list.InsertItem(m_list.GetItemCount(), displayName, iconIndex);
	m_list.SetItemText(iItemIndex, 1, info.getCompanyName().c_str());
	m_list.SetItemText(iItemIndex, 2, info.getDescription().c_str());
	m_list.SetItemText(iItemIndex, 3, info.getFilePath().c_str());

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
END_MESSAGE_MAP()


// CDlgProgramControl ��Ϣ�������
void CDlgProgramControl::OnBnClickedBtnAdd()
{
	// ���ļ�
	TCHAR * FILE_FILTER = _T("Exectuable files(*.exe)|*.exe|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, FILE_FILTER);
	if (IDOK == dlg.DoModal()) {
			// ��ȡ��Ϣ
		CFileInfo info((LPCTSTR)dlg.GetPathName());
		int iIndex = addNewFile(info);
		if (iIndex < 0) {
			AfxMessageBox(IDS_DLG_PROGRAM_CONTROL_DUPLICATE_ITEM, MB_OK | MB_ICONEXCLAMATION);
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

	// ��ʼ��ImageList
	m_imagelist.Create(16, 16, ILC_COLOR24 | ILC_MASK, 50, 5);
	HICON hIcon;
	VERIFY(hIcon = AfxGetApp()->LoadIcon(IDI_DEFAULT));
	VERIFY(0 == m_imagelist.Add(hIcon));
	VERIFY(1 == m_imagelist.Add(hIcon));


	// ��ʼ��listCtrl
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

	// ��������
	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgProgramControl::deleteJustFromUI(const int nItem) {
	assert (-1 != nItem);
	// ����ɾ�������������һ�����û�����Apply����OK��ťʱִ��ɾ��
	ITEMDATA * data = (ITEMDATA*)m_list.GetItemData(nItem);
	if (NULL != data) {
		deleteItem(data->fullPath, nItem);
		SetModify(true);

		// ���б���ɾ��
		removeItemData(data->fullPath.c_str());
	}
	m_list.DeleteItem(nItem);	// ��ListCtrl��ɾ����ǰ��
}
void CDlgProgramControl::OnBnClickedBtnDel()
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos) {
		// ��ȡѡ�е��
		int nItem = m_list.GetNextSelectedItem(pos);
		if (nItem != -1) {
			deleteJustFromUI(nItem);
		}
	} 
}

void CDlgProgramControl::OnBnClickedChkEnableAppcontrol()
{
	SetModify(true);
}
