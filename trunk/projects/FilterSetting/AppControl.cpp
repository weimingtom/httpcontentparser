// AppControl.cpp : CAppControl µÄÊµÏÖ

#include "stdafx.h"
#include "AppControl.h"
#include ".\globalvariable.h"
#include <com\resultvalue.h>
#include <typeconvert.h>
#include <programcontrol.h>
#include <comdef.h>
#include <utility\strutility.h>
#include ".\appcontrol.h"
#include <logger_name.h>

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
STDMETHODIMP CAppControl::checkApp(BSTR fullpath, VARIANT_BOOL* result)
{
	*result = g_configuration.getProgramControl()->check((TCHAR*)_bstr_t(fullpath));
	if (VARIANT_TRUE == *result) {
		LOGGER_DEBUG_WRITE_DATA(FILTERSETTING_LOGGER_DEBUG, "pass app check", (char*)_bstr_t(fullpath));
	} else {
		LOGGER_DEBUG_WRITE_DATA(FILTERSETTING_LOGGER_DEBUG, "block app check", (char*)_bstr_t(fullpath));
	}
	return S_OK;
}

STDMETHODIMP CAppControl::isSettingEnabled(VARIANT_BOOL* enabled)
{
	*enabled = convert(g_configuration.getProgramControl()->isSettingEnabled());
	return S_OK;
}

STDMETHODIMP CAppControl::enable(VARIANT_BOOL enabled)
{
	g_configuration.getProgramControl()->enable(convert(enabled));
	return S_OK;
}
