#include "stdafx.h"
#include ".\progresscheck.h"
#include <stdlib.h>
#include <tchar.h>

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

	enabled_ = true;
}