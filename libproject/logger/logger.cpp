// logger.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "logger.h"



#define DEBUG_LOGGER_FILE ".\\LOG\\DEBUG.LOG"
#define APP_LOGGER_FILE		".\\LOG\\APP.LOG"

#include <boost/logging/format.hpp>

typedef boost::logging::logger_format_write< > log_type;

BOOST_DECLARE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DECLARE_LOG(g_log_app, log_type)
BOOST_DECLARE_LOG(g_log_dbg, log_type)


#define __LDBG__ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug )
#define __LAPP__ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), info )


BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DEFINE_LOG(g_log_app, log_type )
BOOST_DEFINE_LOG(g_log_dbg, log_type )

LOGGER_API void set_logger_level(boost::logging::level::type level) {
	g_log_level()->set_enabled(level);
}

LOGGER_API void logger_app(std::stringstream &s) {
	__LAPP__<<s.str().c_str();
}
LOGGER_API void  logger_debug(std::stringstream &s) {
	__LDBG__<<s.str().c_str();
}


void init_debug_logger(const char * filename, bool enable_cout, bool disable_cache)	  { 
	using namespace boost::logging;
    g_log_dbg()->writer().add_destination( destination::file(filename, destination::file_settings().do_append(true) ));		
	g_log_dbg()->writer().add_formatter( formatter::time(" [$yyyy-$MM-$dd $hh:$mm.$ss] ") );		
    g_log_dbg()->writer().add_formatter( formatter::append_newline() );	
	if (true == enable_cout) {
		g_log_dbg()->writer().add_destination( destination::cout() );	
	}

	 if (true == disable_cache) {
		 g_log_dbg()->turn_cache_off();
	}

	 g_log_dbg()->mark_as_initialized();
}		

void init_app_logger(const char * filename, bool enable_cout, bool disable_cache)	  { 
	using namespace boost::logging;
    g_log_app()->writer().add_destination( destination::file(filename, destination::file_settings().do_append(true) ));		
	g_log_app()->writer().add_formatter( formatter::time(" [$yyyy-$MM-$dd $hh:$mm.$ss] ") );		
    g_log_app()->writer().add_formatter( formatter::append_newline() );	
	if (true == enable_cout) {
		g_log_app()->writer().add_destination( destination::cout() );	
	}

	if (true == disable_cache) {
		 g_log_app()->turn_cache_off();
	}

	g_log_app()->mark_as_initialized();
}		

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
