#include "StdAfx.h"
#include ".\registryinfo.h"
#include ".\xinstall.h"

RegisterInfo::RegisterInfo(void)
{
}

RegisterInfo::~RegisterInfo(void)
{
}

bool RegisterInfo::intacted() {
	// �鿴SPI�Ƿ�װ
	CXInstall install;
	if (!install.IsInstalled())
		return false;

	// �鿴COM Service�Ƿ�װ
	
	return true;
}
