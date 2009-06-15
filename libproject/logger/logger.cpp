// logger.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "logger.h"
#include "log.h"


#define DEBUG_LOGGER_FILE ".\\LOG\\DEBUG.LOG"
#define APP_LOGGER_FILE		".\\LOG\\APP.LOG"

LOGGER_API void set_logger_level(boost::logging::level::type level) {
	g_log_level()->set_enabled(level);
}

LOGGER_API void logger_app(std::stringstream &s) {
	__LAPP__<<s.str().c_str();
}
LOGGER_API void  logger_debug(std::stringstream &s) {
	__LDBG__<<s.str().c_str();
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		init_debug_logger(DEBUG_LOGGER_FILE);
		init_app_logger(APP_LOGGER_FILE);
		set_logger_level(boost::logging::level::debug);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}