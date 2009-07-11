// drivertest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DriverMngr.h"

AppController g_controller;
int _tmain(int argc, _TCHAR* argv[])
{
	g_controller.begin();

	int a ;
	std::cin>>a;
	g_controller.end();
	return 0;
}

