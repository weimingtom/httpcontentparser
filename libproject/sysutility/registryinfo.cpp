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
	// 查看SPI是否安装
	CXInstall install;
	if (!install.IsInstalled())
		return false;

	// 查看COM Service是否安装
	
	return true;
}
