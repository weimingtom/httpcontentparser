// DlgProcess.cpp : ʵ���ļ�
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

// CDlgProcess �Ի���

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


// CDlgProcess ��Ϣ�������

BOOL CDlgProcess::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	AfxBeginThread(Process, (LPVOID)this, 0, 1, 0, NULL);

	return TRUE;  
}



// ɾ����ݷ�ʽ
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
	// ������Ϣ
	int progress = 0;
	dlg->m_process.SetPos(progress);

	// ж��SPI

	// ɾ����ݷ�ʽ
	progress = 20;
	dlg->m_process.SetPos(progress);

	// ж��COM
	progress = 40;
	AppUtility::UninstallService();
	dlg->m_process.SetPos(progress);

	// ж����ǳ���
	progress = 60;
	AppUtility::UninstallShellExt();
	dlg->m_process.SetPos(progress);

	// ����������
	TCHAR fullpath[MAX_PATH];
	GetUninstallUtility(fullpath, MAX_PATH);
	if (ENOENT == _taccess(fullpath, 0)) {
		// �жϳ����Ƿ���ڣ� �Ƿ������ʾ��
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