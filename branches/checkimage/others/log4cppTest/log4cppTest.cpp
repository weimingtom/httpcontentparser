// log4cppTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>


#define LOG_NAME_OPER	("oper")


#ifndef _PACKETS_GRASPER_LOGGER_DEFINE_GLOBAL_VALUE_
	log4cxx::FileAppender * appender_file_oper = NULL;
#define _PACKETS_GRASPER_LOGGER_DEFINE_GLOBAL_VALUE_
#else
	extern log4cxx::FileAppender * appender_file_oper;
#endif 

inline void LOG_INIT(const TCHAR * install_path) {
	log4cxx::FileAppender * appender_file_oper = new
		log4cxx::FileAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()),
		LOG4CXX_STR("logfile.txt"), false);

	log4cxx::helpers::Pool p;
	appender_file_oper->activateOptions(p);

	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(appender_file_oper));
}

inline void LOG_OPER(TCHAR *msg) {
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOG_NAME_OPER);
	LOG4CXX_INFO(logger, " [" << "hello" <<"] " << msg);
}

int main() {

	LOG_INIT("HELLO");
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOG_NAME_OPER);

	LOG_OPER("hello");
	LOG4CXX_INFO(logger,"Created FileAppender appender");

	return 0;
}
