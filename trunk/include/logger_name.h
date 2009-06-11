#ifndef _INCLUDE_LOGGER_NAME__H__
#define _INCLUDE_LOGGER_NAME__H__

#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <tchar.h>

#define		MAINUI_LOGGER_ERROR				TEXT("mainui_error")
#define		MAINUI_LOGGER_ERROR_FILE		LOG4CXX_STR(".\\LOG\\me.log")
#define		MAINUI_LOGGER_INFO					TEXT("mainui_info")
#define		MAINUI_LOGGER_INFO_FILE			LOG4CXX_STR(".\\LOG\\mi.log")

#endif  // _INCLUDE_LOGGER_NAME__H__