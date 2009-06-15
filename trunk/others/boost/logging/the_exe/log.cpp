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

#include "log.h"


BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DEFINE_LOG(g_log_app, log_type )
BOOST_DEFINE_LOG(g_log_dbg, log_type )


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