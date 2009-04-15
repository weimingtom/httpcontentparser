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
	InstallDate date;
	date.setInstall();
	std::cout<<"Install date: " << date.getInstallData() << std::endl;
	std::cout<<"Installed days : " << date.getInstalledDays() <<std::endl;
}