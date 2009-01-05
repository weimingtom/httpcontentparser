// testCrypt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	EncryptFile(".\\config.xml", ".\\result.txt");
	DecryptFile(".\\result.txt", ".\\deresult.txt");
	return 0;
}

