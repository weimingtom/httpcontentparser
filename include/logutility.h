#ifndef _UTILITY_LOGGER_H__
#define _UTILITY_LOGGER_H__

#include <assert.h>
#include <set>
#include <malloc.h>
#include <time.h>
#include <string>
#include <logsystem\logcatalog.h>
#include <logsystem\loglayout.h>
#include <logsystem\loglistener.h>
#include <logsystem\logger.h>
#include <logsystem\fileloglistener.h>
#include <syncobject\syncobject.h>
#include <utility\syncutility.h>


#define LOG_UTILITY_NEW_LINE ("\n")

class LogUtility {
public:
	void InitLogger(const std::string &loggername, const std::string &filename) {
		// 创建Listener
		LogSystem::Logger *log = LogSystem::LogCatalog::getInstance()->createLogger(loggername);	 
		// 提取文件名，并加上.log
		LogSystem::FileLogListener *listener = new LogSystem::FileLogListener(filename, loggername);
		log->AddListener(listener);

		listeners_.insert(listener);
	}

	void beginWrite(const std::string &loggername) {
		time_t t = time(0); 
		char tmp[1024];
		strftime(tmp, sizeof(tmp), "[%Y/%m/%d %H:%M:%S] ",localtime(&t));
		write(tmp, strlen(tmp), loggername);
	}
	void write(const char *buf, const int len, const std::string &loggername) {
		LogSystem::Logger *log = LogSystem::LogCatalog::getInstance()->getLogger(loggername);
		if(log != NULL)
			log->write(buf, len);
	}
	void writeln(const char *buf, const int len, const std::string &loggername) {
		LogSystem::Logger *log = LogSystem::LogCatalog::getInstance()->getLogger(loggername);
		if(log != NULL) {
			log->write(buf, len);
			log->write(LOG_UTILITY_NEW_LINE, strlen(LOG_UTILITY_NEW_LINE));
		}
	}
	void writeln(const std::string &loggername) {
		LogSystem::Logger *log = LogSystem::LogCatalog::getInstance()->getLogger(loggername);
		if(log != NULL)
			log->write(LOG_UTILITY_NEW_LINE, strlen(LOG_UTILITY_NEW_LINE));
	}
	void endWrite(const std::string &loggername) {
		LogSystem::Logger *log = LogSystem::LogCatalog::getInstance()->getLogger(loggername);
		if(log != NULL)
			log->write(LOG_UTILITY_NEW_LINE, strlen(LOG_UTILITY_NEW_LINE));
	}

	void destroyAll() {
		LogSystem::LogCatalog::getInstance()->DestroyAll();
		SyncObjects::SyncObject::DestoryAll();
		destroyAllListener();
	}
	LogUtility() {}
	~LogUtility() {}
private:
	static const std::string new_line;
	void destroyAllListener() {
		std::set<LogSystem::FileLogListener*>::iterator iter = listeners_.begin();
		for (; iter != listeners_.end(); ++iter) {
			delete *iter;
		}
		listeners_.clear();
	}
	std::set<LogSystem::FileLogListener*> listeners_;
};

#endif  // _UTILITY_LOGGER_H__