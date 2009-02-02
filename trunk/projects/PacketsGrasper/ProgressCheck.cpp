#include "stdafx.h"
#include ".\progresscheck.h"

ProgressCheck::ProgressCheck(void)
{
	enabled_ = true;
}

ProgressCheck::~ProgressCheck(void)
{
}

// ��֤Ӧ�ó����Ƿ�Ӧ�ñ�����
void ProgressCheck::checkCallProgress() {
	// �Ƚ��Ƿ���svchost
	TCHAR caller[MAX_PATH];
	GetModuleFileName(NULL, caller, MAX_PATH);
	_tcslwr(caller);

	TCHAR sysDir[MAX_PATH], svchost[MAX_PATH];
	GetSystemDirectory(sysDir, MAX_PATH);
	_stprintf(svchost, "%s\\system32\\svchost.exe", sysDir);
	if (0 == _tcscmp(caller, svchost)) {
		enabled_ =  false;
	}

	enabled_ = true;
}