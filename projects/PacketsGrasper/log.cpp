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

#include "stdafx.h"
#include "log.h"
#include <DebugOutput.h>

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

#ifdef DEBUG
	g_log_level()->set_enabled(boost::logging::level::debug);
#else
	g_log_level()->set_enabled(boost::logging::level::info);
#endif
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

#ifdef DEBUG
	g_log_level()->set_enabled(boost::logging::level::debug);
#else
	g_log_level()->set_enabled(boost::logging::level::info);
#endif
}		


namespace {
	const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len) {
		TCHAR dir[MAX_PATH], driver[MAX_PATH];
		_tsplitpath(filename, driver, dir, NULL, NULL);
		_sntprintf(directory, len, TEXT("%s%s"), driver, dir);
		return directory;
	}


	const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len) {
		TCHAR dir[MAX_PATH], driver[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
		_tsplitpath(fullname, driver, dir, name, ext);
		_sntprintf(ename, len, TEXT("%s%s"), name, ext);
		return ename;
	}
};

void init_logger(HMODULE hModule) {
	TCHAR filename[MAX_PATH], dir[MAX_PATH], callerpath[MAX_PATH], callname[MAX_PATH];
	// 获取DLL的路径
	GetModuleFileName(hModule, filename, MAX_PATH);
	GetFileNameDir(filename, dir, MAX_PATH);

	//获取caller_name
	GetModuleFileName(NULL, callerpath, MAX_PATH);
	GetFileName(callerpath, callname, MAX_PATH);

	_sntprintf(filename, MAX_PATH, "%s\\log\\pgrasper_%s.log", dir, callerpath);
	init_app_logger(filename);
	_sntprintf(filename, MAX_PATH, "%s\\log\\dpgrasper_%s.log", dir, callerpath);
	init_debug_logger(filename);

	g_log_level()->set_enabled(boost::logging::level::debug);
}
