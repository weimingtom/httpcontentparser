// AppControl.cpp : CAppControl 的实现

#include "stdafx.h"
#include "AppControl.h"
#include ".\globalvariable.h"
#include <com\resultvalue.h>
#include <typeconvert.h>
#include <programcontrol.h>
#include <comdef.h>
#include <utility\strutility.h>
#include <DebugOutput.h>
#include ".\appcontrol.h"
#include <apputility.h>
#include <logger\logger.h>


namespace {
bool checkInSameDirectory(LPCTSTR lpstr) {
	TCHAR exefiledir[MAX_PATH]; 
	GetFileNameDir(lpstr, exefiledir, MAX_PATH);
	
	// 获取本文件的路径
	TCHAR myselfdir[MAX_PATH], myfilepath[MAX_PATH];
	GetModuleFileName(NULL, myfilepath, MAX_PATH);
	GetFileNameDir(myfilepath, myselfdir, MAX_PATH);

	if (_tcsstr(myselfdir, exefiledir) != NULL) {
		return true;
	} else {
		return false;
	}
}
};

// CAppControl
STDMETHODIMP CAppControl::AddNewItem(BSTR path) {
	g_configuration.getProgramControl()->addItem((TCHAR*)_bstr_t(path));
	_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Add New Item : "<< (TCHAR*)_bstr_t(path));
	return S_OK;
}


STDMETHODIMP CAppControl::RemoveItem(BSTR path) {
	g_configuration.getProgramControl()->removeitem((TCHAR*)_bstr_t(path));
	_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Remove New Item : "<< (TCHAR*)_bstr_t(path));
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
	// 如果是在本目录下的文件永远都能够运行
	if (true == checkInSameDirectory((TCHAR*)_bstr_t(fullpath))) {
		_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Check Item :  "<< (TCHAR*)_bstr_t(fullpath)<<" In the same path with ext");
		*result = VARIANT_TRUE; 
	} else {
		*result = convert(g_configuration.getProgramControl()->check((TCHAR*)_bstr_t(fullpath)));

		__LTRC__(((VARIANT_TRUE == *result) ? "pass " : "block ")<<"app check "<< (char*)_bstr_t(fullpath));
		_DEBUG_STREAM_TRC_("[Family007 Service]  [" <<__FUNCTION__<<"] Check Item :  "
			<< (TCHAR*)_bstr_t(fullpath)
			<< "  result : "<<(VARIANT_TRUE == *result) ? "passed" : "blocked");
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
