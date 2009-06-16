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

BOOST_DEFINE_LOG_FILTER(g_log_level, boost::logging::level::holder ) 
BOOST_DEFINE_LOG(g_log_app, log_type )
BOOST_DEFINE_LOG(g_log_dbg, log_type )

