// testCrypt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	yanglei_utility::EncryptFile(".\\config.xml", ".\\result.txt");
	yanglei_utility::DecryptFile(".\\result.txt", ".\\deresult.txt");
	return 0;
}

