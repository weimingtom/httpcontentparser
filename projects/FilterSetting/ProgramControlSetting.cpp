// ProgramControlSetting.cpp : CProgramControlSetting µÄÊµÏÖ

#include "stdafx.h"
#include "ProgramControlSetting.h"
#include ".\programcontrolsetting.h"
#include ".\globalvariable.h"
#include <programcontrol.h>
#include <comdef.h>
#include <utility\strutility.h>

// CProgramControlSetting
STDMETHODIMP CProgramControlSetting::AddNewItem(BSTR path) {
	g_configuration.getProgramControl()->addItem((TCHAR*)_bstr_t(path));
	return S_OK;
}


STDMETHODIMP CProgramControlSetting::RemoveItem(BSTR path) {
	g_configuration.getProgramControl()->removeitem((TCHAR*)_bstr_t(path));
	return S_OK;
}

STDMETHODIMP CProgramControlSetting::GetFirstItem(BSTR* path) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getFirstItem(&fullpath, &fileinfo);
	if (0 != result)
		*path = _bstr_t(fullpath.c_str());
	else
		*path = _bstr_t("");
	return S_OK;
}

STDMETHODIMP CProgramControlSetting::GetNextItem(BSTR cur, BSTR* nxt) {
	ProgramControl::FILEINFO * fileinfo;
	strutility::_tstring fullpath;
	int result = g_configuration.getProgramControl()->getNextItem((TCHAR*)_bstr_t(cur), &fullpath, &fileinfo);
	if (0 != result) 
		*nxt = _bstr_t(fullpath.c_str());
	else
		*nxt = _bstr_t("");
	return S_OK;
}
