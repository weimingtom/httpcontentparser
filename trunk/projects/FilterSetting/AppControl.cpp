// AppControl.cpp : CAppControl µÄÊµÏÖ

#include "stdafx.h"
#include "AppControl.h"
#include ".\globalvariable.h"
#include <programcontrol.h>
#include <comdef.h>
#include <utility\strutility.h>

// CAppControl
STDMETHODIMP CAppControl::AddNewItem(BSTR path) {
	g_configuration.getProgramControl()->addItem((TCHAR*)_bstr_t(path));
	return S_OK;
}


STDMETHODIMP CAppControl::RemoveItem(BSTR path) {
	g_configuration.getProgramControl()->removeitem((TCHAR*)_bstr_t(path));
	return S_OK;
}

STDMETHODIMP CAppControl::GetFirstItem(BSTR* path) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getFirstItem(&fullpath, &fileinfo);
	if (0 != result)
		*path = _bstr_t(fullpath.c_str());
	else
		*path = _bstr_t("");
	return S_OK;
}

STDMETHODIMP CAppControl::GetNextItem(BSTR cur, BSTR* nxt) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getNextItem((TCHAR*)_bstr_t(cur), &fullpath, &fileinfo);
	if (0 != result) 
		*nxt = _bstr_t(fullpath.c_str());
	else
		*nxt = _bstr_t("");
	return S_OK;
}