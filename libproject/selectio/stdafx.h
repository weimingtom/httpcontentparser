// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <afxwin.h>
#include <ws2spi.h>
#include <io.h>				

 
#ifdef _DEBUG
#	pragma comment(lib, "tinyxmld.lib")
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "apputilityd.lib")
#	pragma comment(lib, "antiporndll.lib")
#else
#	pragma comment(lib, "tinyxml.lib")
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "apputility.lib")
#	pragma comment(lib, "antiporndll.lib")
#endif

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
