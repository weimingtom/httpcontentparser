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

// the_exe.cpp : Defines the entry point for the console application.


#include "log.h"


int main(int argc, char* argv[])
{
	init_app_logger("app", true);
	init_debug_logger("debug", true);
	using namespace boost::logging;
	g_log_level()->set_enabled(level::debug);
	int i = 1;
	LDBG_ << "this is so cool " << i++;
	LERR_<< "first error " << i++;

	std::string hello = "hello", world = "world";
	LDBG_<< hello << ", " << world;

	using namespace boost::logging;
	g_log_level()->set_enabled(level::error);
	LTRC_<< "this will not be written anywhere";
	LDBG_<< "this won't be written anywhere either";
	LAPP_<< "second error " << i++;

	g_log_level()->set_enabled(level::info);
	LAPP_ << "good to be back ;) " << i++;
	LERR_ << "third error " << i++;

	return 0;
}

