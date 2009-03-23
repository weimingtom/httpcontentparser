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

// 验证应用程序是否应该被处理
void ProgressCheck::checkCallProgress() {
	// 比较是否是svchost
	TCHAR caller[MAX_PATH];
	GetModuleFileName(NULL, caller, MAX_PATH);
	_tcslwr(caller);

	enabled_ = true;
}