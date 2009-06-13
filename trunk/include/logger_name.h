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

#define		FILTERSETTING_LOGGER_ERROR	TEXT("Service_error")
#define		FILTERSETTING_LOGGER_FILE		LOG4CXX_STR(".\\log\\services.log")


#define LOGGER_WRITE(LOGGER_NAME, LOGGER_TEXT)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_FUNC_FAILED(LOGGER_NAME, FUNC_NAME, RETURE_VALUE)	{TCHAR buffer[1024];		\
	LPVOID lpMsgBuf;	\
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |     FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,	\
			NULL,     GetLastError(),     0,   (LPTSTR) &lpMsgBuf,   0,    NULL);	\
	_sntprintf(buffer, 1024, "{%s} Failed On call %s, return value is %d, lastError is %d : %s", __FUNCTION__, (FUNC_NAME), RETURE_VALUE, GetLastError(), lpMsgBuf);		\
	LocalFree( lpMsgBuf );	\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_ERROR(LOGGER_NAME, LOGGER_TEXT, RESULT) { TCHAR buffer[1024]; \
	_sntprintf(buffer, 1024, "{%s} %s HRESULT Value : %8Xh", __FUNCTION__, (LOGGER_TEXT), RESULT);		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_FAILED(LOGGER_NAME, LOGGER_TEXT, RESULT) { TCHAR buffer[1024]; \
	_sntprintf(buffer, 1024, "{%s} Failed on {%s}; HRESULT Value : %8Xh", __FUNCTION__, (LOGGER_TEXT), RESULT);		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_DESCRIPTION(LOGGER_NAME, LOGGER_TEXT) {TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} COM_ERROR : %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}


inline void initLogger(log4cxx::LogString FILEAPPENDER) {
	using namespace log4cxx;
	log4cxx::FileAppender * appender_file_oper = new log4cxx::FileAppender();
	appender_file_oper->setFile(FILEAPPENDER);
	appender_file_oper->setLayout(LayoutPtr(new SimpleLayout()));
	appender_file_oper->setAppend(true);
	log4cxx::helpers::Pool p;
	appender_file_oper->activateOptions(p);
	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(appender_file_oper));
}


#endif  // _INCLUDE_LOGGER_NAME__H__