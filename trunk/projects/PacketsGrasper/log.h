/**
 Boost Logging library

 Author: John Torjo, www.torjo.com

 Copyright (C) 2007 John Torjo (see www.torjo.com for email)

 Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
          http://www.boost.org/LICENSE_1_0.txt)

 See http://www.boost.org for updates, documentation, and revision history.
 See http://www.torjo.com/log2/ for more details
*/

#ifndef LOG_H
#define LOG_H
#pragma once

#include <boost/logging/format.hpp>

typedef boost::logging::logger_format_write< > log_type;

extern TCHAR g_caller_name[MAX_PATH];

BOOST_DECLARE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DECLARE_LOG(g_log_app, log_type)
BOOST_DECLARE_LOG(g_log_dbg, log_type) 

#define LTRC_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug )  <<"[PacketGrasper]  [TRACE]{@"<<__FUNCTION__<<"} "
#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug ) <<"[[PacketGrasper]  DEBUG]{@"<<__FUNCTION__<<"} "

// 其他三个用于同时记录
#define LERR_(MSG)	BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), error ) \
		<<"[PacketGrasper]  [ERROR]{"<<__FUNCTION__<<"} "	<<MSG <<" called by app "<<g_caller_name;
#define LAPP_(MSG)	BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), info )	\
		<<"[PacketGrasper]  [INFOM]{"<<__FUNCTION__<<"} " <<MSG<<" called by app " << g_caller_name;
#define LFAT_(MSG)	BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), fatal )	\
		<<"[PacketGrasper]  [FATAL]{"<<__FUNCTION__<<"} " << MSG<<" called by app " << g_caller_name;


void init_debug_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);
void init_app_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);	
void init_logger(HMODULE hModule);

#define LTRC_WITHOUT	 BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug )  <<"[PacketGrasper]"
class scope_logger_helper {
public:
	scope_logger_helper(const TCHAR * logger_text) : _logger_text_(logger_text){
		assert(logger_text != NULL);
		LTRC_WITHOUT<<_logger_text_<<" @scope_begin";
	}
	
	~scope_logger_helper() {
		LTRC_WITHOUT<<_logger_text_<<" @scope_end";
	}
	
	const char * _logger_text_;
};

#define __AUTO_FUNCTION_SCOPE_TRACE__		scope_logger_helper __scope_logger_helper__(__FUNCTION__)

#endif
