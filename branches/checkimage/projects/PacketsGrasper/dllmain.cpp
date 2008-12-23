#include "stdafx.h"
#include "overlapped.h"
#include "spidefines.h"
#include <com\Rules_management_exe.h>
#include <com\Rules_management_exe_i.c>

#pragma data_seg(".inidata")
	int				m_iRefCount		= 0;
#pragma data_seg()

CRITICAL_SECTION	gCriticalSection;			// ����α�������
WSPPROC_TABLE		NextProcTable   ;			// ����30�������ṩ��ָ��
TCHAR				m_sProcessName[MAX_PATH];	// ���浱ǰ��������

IExeRulesChecker * pRulesChecker_ = NULL;
IExeRulesSetting * pRulesSetting_ = NULL;

BOOL WINAPI DllMain(
	HINSTANCE	hModule, 
    DWORD		ul_reason_for_call, 
    LPVOID		lpReserved
)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		CoInitializeEx(NULL, 0x0);
 		GetModuleFileName(NULL, m_sProcessName, MAX_PATH);

		InitializeCriticalSection(&gCriticalSection);


		EnterCriticalSection(&gCriticalSection);
		{
			// ��ʼ��COM
			HRESULT hResult;
				hResult = CoCreateInstance(CLSID_ExeRulesChecker,
			NULL, CLSCTX_ALL, IID_IExeRulesChecker,(void**)&pRulesChecker_);
			hResult = CoCreateInstance(CLSID_ExeRulesSetting,
				NULL, CLSCTX_ALL, IID_IExeRulesSetting,(void**)&pRulesSetting_);

			m_iRefCount ++;
			DP1("DllMain Attach Count %d", m_iRefCount);
		}
		LeaveCriticalSection(&gCriticalSection);

		ODS2(m_sProcessName,_T(" Loading ..."));
	}
	else if(ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		EnterCriticalSection(&gCriticalSection);
		{
			m_iRefCount -- ;
			DP1("DllMain Attach Count %d", m_iRefCount);
		}
		LeaveCriticalSection(&gCriticalSection);

		ODS2(m_sProcessName,_T(" Exit ..."));
		CoUninitialize();
	}

	return TRUE;
}