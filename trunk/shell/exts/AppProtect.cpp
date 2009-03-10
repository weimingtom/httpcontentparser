// AppProtect.cpp : CAppProtect µÄÊµÏÖ

#include "stdafx.h"
#include "AppProtect.h"


// CAppProtect
UINT CAppProtect::CopyCallback(HWND hwnd, UINT wFunc, UINT wFlags, LPCTSTR pszSrcFile,  DWORD dwSrcAttribs, LPCTSTR pszDestFile, DWORD dwDestAttribs) {
	return IDYES;
}

HRESULT CAppProtect::GetEnumFlags(IShellFolder *psf,  LPCITEMIDLIST pidlFolder, HWND *phwnd, DWORD *pgrfFlags) {
	return S_OK;
}

HRESULT CAppProtect::ShouldShow(IShellFolder *psf, LPCITEMIDLIST pidlFolder, LPCITEMIDLIST pidlItem) {
	return S_OK;
}