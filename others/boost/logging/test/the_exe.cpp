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
	int i = 0;
	init_debug_logger("test.log", true);
	init_app_logger("app.log", true);
	LDBG_ << "beginning of exe log" << ++i;
	LDBG_ << "message from exeE" << ++i;

	LERR_ << "  message from exe" << ++i;
	LTRC_<<  " message 2 " <<++i;

	LERR_ << __FUNCTION__  << "end of exe log " << ++i;
	return 0;
}

