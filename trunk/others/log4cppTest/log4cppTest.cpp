// log4cppTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



using namespace log4cxx;
using namespace log4cxx::helpers;

namespace com {
	namespace foo {
		class Bar {
			static log4cxx::LoggerPtr logger;
		public:
			void doIt();
		};
	}
}



using namespace com::foo;
LoggerPtr Bar::logger(Logger::getLogger("com.foo.bar"));

void Bar::doIt() {
   LOG4CXX_DEBUG(logger, "Did it again!");
}

LoggerPtr logger(Logger::getLogger("MyApp"));

int _tmain(int argc, _TCHAR* argv[])
{

	logger->setLevel(log4cxx::Level::getInfo());

	BasicConfigurator::configure();
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("MyApp"));
	const char* region = "World";
	// This request is enabled, because WARN >= INFO.
    LOG4CXX_WARN(logger, "Low fuel level.");
	LOG4CXX_INFO(logger, "Simple message text.");
	LOG4CXX_INFO(logger, "Hello, " << region);
	LOG4CXX_DEBUG(logger, L"Iteration ");


	Bar bar;
	bar.doIt();

	return 0;
}

