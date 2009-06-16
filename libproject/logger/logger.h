#ifndef _LOGGER_H__
#define _LOGGER_H__


#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#include <sstream>
#include <boost/logging/format.hpp>



LOGGER_API void set_logger_level(boost::logging::level::type type);
LOGGER_API void logger_debug(std::stringstream &s);
LOGGER_API void logger_app(std::stringstream &s);
LOGGER_API void init_debug_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);
LOGGER_API void init_app_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);	

#define LOGGER_DEBUG_OUTPUT(HEADER, FMT) { std::stringstream __output_debug_string_stream__;	\
	__output_debug_string_stream__<<HEADER<<FMT;	\
	logger_debug(__output_debug_string_stream__);}\

#define LOGGER_APP_OUTPUT(HEADER, FMT) { std::stringstream __output_debug_string_stream__;	\
	__output_debug_string_stream__<<HEADER<<FMT;	\
	logger_app(__output_debug_string_stream__);}\

#define __LTRC__(FMT) 	LOGGER_DEBUG_OUTPUT("[TRACE] {"<<__FUNCTION__<<"} ", FMT);
#define __LDBG__(FMT) 	LOGGER_DEBUG_OUTPUT("[DEBUG] {"<<__FUNCTION__<<"} ", FMT);

// 其他三个用于同时记录
#define __LERR__(FMT) 	LOGGER_APP_OUTPUT("[ERROR] {"<<__FUNCTION__<<"} ", FMT);
#define __LAPP__(FMT) 	LOGGER_APP_OUTPUT("[INFOM] {"<<__FUNCTION__<<"} ", FMT);
#define __LFAT__(FMT) 	LOGGER_APP_OUTPUT("[FATAL] {"<<__FUNCTION__<<"} ", FMT);

#endif 

