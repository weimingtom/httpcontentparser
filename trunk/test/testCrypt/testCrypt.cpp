// testCrypt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	EncryptFile(".\\config.xml", ".\\result.txt");
	DecryptFile(".\\result.txt", ".\\deresult.txt");
	return 0;
}

