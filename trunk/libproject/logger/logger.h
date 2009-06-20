#ifndef _LOGGER_H__
#define _LOGGER_H__


#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#include <sstream>
#include <iostream>
#include <ios>
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

class scope_logger_helper {
public:
	scope_logger_helper(const std::stringstream s)  {
		_s_<<s.str();
	}
	scope_logger_helper(const TCHAR * logger_text) {
		assert(logger_text != NULL);
		_s_<<logger_text;
		LOGGER_DEBUG_OUTPUT("[SCOPE TRACE] ",  _s_.str().c_str()<<" @scope_begin");
	}
	
	~scope_logger_helper() {
		LOGGER_DEBUG_OUTPUT("[SCOPE TRACE] ", _s_.str().c_str()<<" @scope_end");
	}
	
	std::stringstream _s_;
};

#define __AUTO_FUNCTION_SCOPE_TRACE__			scope_logger_helper __scope_logger_helper__(__FUNCTION__)
#define __DEINFED_MSG_SCOPE_TRACE__(MSG)		{	std::stringstream s; \
	s<<MSG;	\
	scope_logger_helper __scope_logger_helper__(s.str().c_str()); }
#endif 

