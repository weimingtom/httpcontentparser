// zlib_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <zlib\zconf.h>
#include <zlib\zlib.h>

#include <iostream>
using namespace std;

#pragma comment(lib, "zlib1.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	char dest1[10240], dest2[10240];
	const char *p = "hello world";

	int dest_len = 10240;
	compress((Bytef*)dest1, (uLongf*)&dest_len, (Bytef*)p, strlen(p));

	uncompress((Bytef*)dest2, (uLongf*)&dest_len, (Bytef*)dest1, dest_len);

	cout<<dest2<<endl;
	return 0;
}

