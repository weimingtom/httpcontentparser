#ifndef STDAFX_H
#define STDAFX_H


#include <ws2spi.h>
#include <windows.h>
#include <io.h>				
#include <tchar.h>

 
#ifdef _DEBUG
#	pragma comment(lib, "utilitymtd.lib")
#else
#	pragma comment(lib, "utilitymt.lib")
#endif

#endif //STDAFX_H