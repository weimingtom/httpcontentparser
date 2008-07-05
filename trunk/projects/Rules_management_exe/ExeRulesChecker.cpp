// ExeRulesChecker.cpp : CExeRulesChecker µÄÊµÏÖ

#include "stdafx.h" 
#include "ExeRulesChecker.h"
#include "globaldata.h"
extern CGlobalData g_globalData;
// CExeRulesChecker   
 
STDMETHODIMP CExeRulesChecker::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExeRulesChecker
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
STDMETHODIMP CExeRulesChecker::checkIp(ULONG ip, VARIANT_BOOL* bFiltered) {
	*bFiltered = (VARIANT_BOOL)g_globalData.checkIP(ip);
	return S_OK;
}
