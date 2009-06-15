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

BOOST_DECLARE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DECLARE_LOG(g_log_app, log_type)
BOOST_DECLARE_LOG(g_log_dbg, log_type)


#define __LDBG__ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_dbg(), g_log_level(), debug )
#define __LAPP__ BOOST_LOG_USE_LOG_IF_LEVEL(g_log_app(), g_log_level(), info )

void init_debug_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);
void init_app_logger(const char * filename, bool enable_cout = false, bool disable_cache=false);	


#endif
