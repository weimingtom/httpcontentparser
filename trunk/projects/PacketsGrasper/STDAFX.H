#ifndef STDAFX_H
#define STDAFX_H


#include <ws2spi.h>
#include <windows.h>
#include <io.h>				
#include <tchar.h>

 
#ifdef _DEBUG
#	pragma comment(lib, "utilitymtd.lib")
#	pragma comment(lib, "selectiod.lib")
#else
#	pragma comment(lib, "utilitymt.lib")
#	pragma comment(lib, "selectio.lib")
#endif

#endif //STDAFX_H