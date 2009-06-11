// DlgProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "DlgProcess.h"
#include ".\dlgprocess.h"
#include <AppInstallValidate.h>
#include <app_constants.h>
#include <apputility.h>
#include <stdlib.h>
#include <stdio.h>
#include <shlwapi.h>
#include <comdef.h>
#include <io.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <softwareStatus.h>

// CDlgProcess 对话框

namespace {
	TCHAR * getProgramFolder(TCHAR * folder, const int len);
};

IMPLEMENT_DYNAMIC(CDlgProcess, CDialog)
CDlgProcess::CDlgProcess(CWnd* pParent /*=NULL*/)
: CDialog(CDlgProcess::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgProcess::~CDlgProcess()
{
}

void CDlgProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_process);
}


BEGIN_MESSAGE_MAP(CDlgProcess, CDialog)
END_MESSAGE_MAP()


// CDlgProcess 消息处理程序

BOOL CDlgProcess::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	AfxBeginThread(Process, (LPVOID)this, 0, 1, 0, NULL);

	return TRUE;  
}



// 删除快捷方式
void DeleteShortcut() {
}

void SetUninstallStatus() {
	ISnowmanSetting * pSetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
		IID_ISnowmanSetting, (LPVOID*)&pSetting);
	if (FAILED(hr)) {
		return ;
	}

	pSetting->setApplicationStatus(SNOWMAN_STATUS_UNINSTALL);
	pSetting->Release();
}

UINT __cdecl Process( LPVOID pParam ) {
	CDlgProcess * dlg = (CDlgProcess*)pParam;
	// 处理消息
	int progress = 0;
	dlg->m_process.SetPos(progress);

	// 卸载SPI

	// 删除快捷方式
	progress = 20;
	dlg->m_process.SetPos(progress);

	// 卸载COM
	progress = 40;
	AppUtility::UninstallService();
	dlg->m_process.SetPos(progress);

	// 卸载外壳程序
	progress = 60;
	AppUtility::UninstallShellExt();
	dlg->m_process.SetPos(progress);

	// 设置启动项
	TCHAR fullpath[MAX_PATH];
	GetUninstallUtility(fullpath, MAX_PATH);
	if (ENOENT == _taccess(fullpath, 0)) {
		// 判断程序是否存在， 是否给出提示？
		CString title, tips;
		title.LoadString(AfxGetInstanceHandle(), IDS_TITLE);
		tips.LoadString(AfxGetInstanceHandle(), IDS_FILE_NOT_FOUND);
		::MessageBox(NULL, tips, title, MB_OK | MB_ICONEXCLAMATION);
		dlg->EndDialog(IDCANCEL);
		return 0;
	}

	RegisterAutoRun(fullpath, TRUE);

	progress = 100;
	dlg->m_process.SetPos(progress);
	Sleep(500);

	dlg->EndDialog(IDOK);
	return 0;
}

TCHAR * getProgramFolder(TCHAR * szPath, const int len) {
	IMalloc * pShellMalloc = NULL;        // A pointer to the shell's IMalloc interface
	IShellFolder *psfParent;              // A pointer to the parent folder object's IShellFolder interface.
	LPITEMIDLIST pidlItem = NULL;         // The item's PIDL.
	LPITEMIDLIST pidlRelative = NULL;     // The item's PIDL relative to the parent folder.
	STRRET str;                           // The structure for strings returned from IShellFolder.

	HRESULT hres = SHGetMalloc(&pShellMalloc);
	if (FAILED(hres)) 	{
		return NULL;
	}

	hres = SHGetSpecialFolderLocation(NULL,
		CSIDL_FAVORITES,
		&pidlItem);
	if (SUCCEEDED(hres)) 	{	
		hres = SHBindToParent(pidlItem,
			IID_IShellFolder,
			(void**)&psfParent,
			(LPCITEMIDLIST*)&pidlRelative);
		if (SUCCEEDED(hres)) 		{
			// Retrieve the path
			memset(&str, 0, sizeof(str));
			hres = psfParent->GetDisplayNameOf(pidlRelative, SHGDN_NORMAL | SHGDN_FORPARSING, &str);
			if (SUCCEEDED(hres)) 	{
				StrRetToBuf(&str, pidlItem, (LPSTR)szPath, MAX_PATH);
			}
			psfParent->Release();
		}
	}

	// Clean up allocated memory
	if (pidlItem) 	{
		pShellMalloc->Free(pidlItem);
	}
	if (pidlRelative) {
		pShellMalloc->Free(pidlRelative);
	}
	pShellMalloc->Release();
	
	return szPath;
}