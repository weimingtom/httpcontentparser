// AppControl.cpp : CAppControl ��ʵ��

#include "stdafx.h"
#include "AppControl.h"
#include ".\globalvariable.h"
#include <com\resultvalue.h>
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

STDMETHODIMP CAppControl::GetFirstItem(BSTR* path, LONG *hasValue) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getFirstItem(&fullpath, &fileinfo);
	if (0 != result) {
		*path = _bstr_t(fullpath.c_str());
		*hasValue =SELF_COM_SUCCEED;
	} 	else {
		*path = _bstr_t("");
		*hasValue = SELF_COM_FAILED;
	}
	return S_OK;
}

STDMETHODIMP CAppControl::GetNextItem(BSTR cur, BSTR* nxt, LONG * hasValue) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getNextItem((TCHAR*)_bstr_t(cur), &fullpath, &fileinfo);
	if (0 != result) {
		*nxt = _bstr_t(fullpath.c_str());
		*hasValue = SELF_COM_SUCCEED;
	}	else {
		*nxt = _bstr_t("");
		*hasValue = SELF_COM_FAILED;
	}
	return S_OK;
}