#ifndef STDAFX_H
#define STDAFX_H

#include <afxwin.h>
#include <ws2spi.h>
#include <io.h>


// log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

 
#ifdef _DEBUG
#	pragma comment(lib, "utilityd.lib")
#	pragma comment(lib, "selectiod.lib")
#	pragma comment(lib, "ServicesUtilityd.lib")
#	pragma comment(lib, "log4cxxd.lib")
#else
#	pragma comment(lib, "utility.lib")
#	pragma comment(lib, "selectio.lib")
#	pragma comment(lib, "ServicesUtility.lib")
#	pragma comment(lib, "log4cxx.lib")
#endif

#endif //STDAFX_H