// configfilereader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <crypt.h>

#pragma comment(lib, "crypt.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR decryptfile[] = ".\\configg.xml";
	yanglei_utility::DecryptFile((LPTSTR)".\\nwist.dll", decryptfile);
	return 0;
}

