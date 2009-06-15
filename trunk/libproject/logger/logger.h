#ifndef _LOGGER_H__
#define _LOGGER_H__


#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#include <sstream>
#include <boost/logging/format.hpp>



LOGGER_API void set_logger_leve(boost::logging::level::type type);
LOGGER_API void logger_debug(std::stringstream &s);
LOGGER_API void logger_app(std::stringstream &s);

#define LOGGER_DEBUG_OUTPUT(HEADER, FMT) { std::stringstream __output_debug_string_stream__;	\
	__output_debug_string_stream__<<HEADER<<FMT;	\
	logger_debug(__output_debug_string_stream__.str().c_str());}\

#define LOGGER_APP_OUTPUT(HEADER, FMT) { std::stringstream __output_debug_string_stream__;	\
	__output_debug_string_stream__<<HEADER<<FMT;	\
	logger_app(__output_debug_string_stream__.str().c_str());}\

#define LTRC_(FMT) 	LOGGER_DEBUG_OUTPUT("[TRACE] {"<<__FUNCTION__<<"} ", FMT);
#define LDBG_(FMT) 	LOGGER_DEBUG_OUTPUT("[DEBUG] {"<<__FUNCTION__<<"} ", FMT);

// 其他三个用于同时记录
#define LERR_(FMT) 	LOGGER_APP_OUTPUT("[ERROR] {"<<__FUNCTION__<<"} ", FMT);
#define LAPP_(FMT) 	LOGGER_APP_OUTPUT("[INFOM] {"<<__FUNCTION__<<"} ", FMT);
#define LFAT_(FMT) 	LOGGER_APP_OUTPUT("[FATAL] {"<<__FUNCTION__<<"} ", FMT);

#endif 

