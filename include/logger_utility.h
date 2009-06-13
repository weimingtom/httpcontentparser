#ifndef _INCLUDE_LOGGER_NAME__H__
#define _INCLUDE_LOGGER_NAME__H__

#include <log4cxx/simplelayout.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/rolling/rollingfileappender.h>
#include <log4cxx/rolling/fixedwindowrollingpolicy.h>
#include <log4cxx/rolling/filterbasedtriggeringpolicy.h>
#include <log4cxx/filter/levelrangefilter.h>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/dailyrollingfileappender.h>
#include <log4cxx/helpers/stringhelper.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#define LOGGER_TRACE_WRITE(LOGGER_NAME, LOGGER_TEXT)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_TRACE_DATA(LOGGER_NAME, LOGGER_TEXT, DATA)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s:%s", __FUNCTION__, (LOGGER_TEXT), DATA);		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE(LOGGER_NAME, LOGGER_TEXT)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_INFO(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WINAPIC_FAILED(LOGGER_NAME, FUNC_NAME, RETURE_VALUE)	{TCHAR buffer[1024];		\
	LPVOID lpMsgBuf;	\
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |     FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,	\
			NULL,     GetLastError(),     0,   (LPTSTR) &lpMsgBuf,   0,    NULL);	\
	_sntprintf(buffer, 1024, "{%s} Failed On call %s, return value is %d, lastError is %d : %s", __FUNCTION__, (FUNC_NAME), RETURE_VALUE, GetLastError(), lpMsgBuf);		\
	LocalFree( lpMsgBuf );	\
	LOG4CXX_ERROR(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_FUNC_RETURN_FAILED(LOGGER_NAME, FUNC_NAME, RETURE_VALUE)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} Failed On call %s, return value is %d", __FUNCTION__, (FUNC_NAME), RETURE_VALUE);		\
	LOG4CXX_ERROR(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_ERROR(LOGGER_NAME, LOGGER_TEXT, RESULT) { TCHAR buffer[1024]; \
	_sntprintf(buffer, 1024, "{%s} %s HRESULT Value : %8Xh", __FUNCTION__, (LOGGER_TEXT), RESULT);		\
	LOG4CXX_ERROR(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_FAILED(LOGGER_NAME, LOGGER_TEXT, RESULT) { TCHAR buffer[1024]; \
	_sntprintf(buffer, 1024, "{%s} Failed on {%s}; HRESULT Value : %8Xh", __FUNCTION__, (LOGGER_TEXT), RESULT);		\
	LOG4CXX_ERROR(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_WRITE_COM_DESCRIPTION(LOGGER_NAME, LOGGER_TEXT) {TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} COM_ERROR : %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_ERROR(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_DEBUG_WRITE(LOGGER_NAME, LOGGER_TEXT)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s", __FUNCTION__, (LOGGER_TEXT));		\
	LOG4CXX_DEBUG(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}

#define LOGGER_DEBUG_WRITE_DATA(LOGGER_NAME, LOGGER_REASON, LOGGER_DATA)	{TCHAR buffer[1024];		\
	_sntprintf(buffer, 1024, "{%s} %s:%s", __FUNCTION__, (LOGGER_REASON), LOGGER_DATA);		\
	LOG4CXX_DEBUG(log4cxx::Logger::getLogger(LOGGER_NAME), buffer);}



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

inline void setLoggerLevel(LPCTSTR logger_name, const log4cxx::LevelPtr & Lev) {
	using namespace log4cxx;
	log4cxx::Logger::getLogger(logger_name)->setLevel(Lev);
}

#endif  // _INCLUDE_LOGGER_NAME__H__