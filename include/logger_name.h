#ifndef _INCLUDE_LOGGER_NAME__H__
#define _INCLUDE_LOGGER_NAME__H__

#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>


#define		MAINUI_LOGGER_ERROR				TEXT("mainui_error")
#define		MAINUI_LOGGER_ERROR_FILE		LOG4CXX_STR(".\\LOG\\me.log")
#define		MAINUI_LOGGER_INFO					TEXT("mainui_info")
#define		MAINUI_LOGGER_INFO_FILE			LOG4CXX_STR(".\\LOG\\mi.log")
#define		REVISION_TEXT								TEXT("2.3.0.1134")


#define LOGGER_WRITE(LOGGER_NAME, LOGGER_TEXT)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "%s : %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}


#endif  // _INCLUDE_LOGGER_NAME__H__