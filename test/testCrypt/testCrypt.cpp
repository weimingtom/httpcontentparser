// testCrypt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	yanglei_utility::EncryptFile(".\\config.xml", ".\\result.txt");
	yanglei_utility::DecryptFile(".\\result.txt", ".\\deresult.txt");
	return 0;
}

