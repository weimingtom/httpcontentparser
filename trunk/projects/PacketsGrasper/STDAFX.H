#ifndef STDAFX_H
#define STDAFX_H

#include <afxwin.h>
#include <ws2spi.h>
#include <io.h>				

 
#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "selectiod.lib")
#	pragma comment(lib, "ServicesUtilityd.lib")
#else
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "selectio.lib")
#	pragma comment(lib, "ServicesUtility.lib")
#endif

#endif //STDAFX_H