// drivertest.cpp : �������̨Ӧ�ó������ڵ㡣
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

