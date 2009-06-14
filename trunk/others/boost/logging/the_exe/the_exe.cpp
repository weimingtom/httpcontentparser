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
	init_logs();
    L_EXE_ << "beginning of exe log" << ++i;
    L_EXE_ << "message from exe - before init_logs on EXE" << ++i;
    
    L_EXE_ << "message from exe - after init_logs on EXE" << ++i;

    L_EXE_ << "end of exe log " << ++i;
	return 0;
}

