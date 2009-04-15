#include "StdAfx.h"
#include ".\installdatetest.h"
#include <softwareencrypt\installdate.h>
#include <iostream>

InstallDateTest::InstallDateTest(void)
{
}

InstallDateTest::~InstallDateTest(void)
{
}


void InstallDateTest::TestInstallDateItem() {
	using namespace software_encrypt;
	setInstall();
	std::cout<<"Install date: " << getInstallData() << std::endl;
	std::cout<<"Installed days : " << getInstalledDays() <<std::endl;
}