#include "precomp.h"
#include ".\logcatalog.h"
#include ".\logger.h"
#include ".\logmsgdispatcher.h"
#include "syncobject\syncobject.h"
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
 
namespace LogSystem {

LogCatalog::LOGGER_MAP LogCatalog::logger_map_;

const std::string LogCatalog::SYNC_OBJECT_NAME = "LogSystem::LogCatalog::CS";

LogCatalog * LogCatalog::getInstance() {
	// 初始化同步对象
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogCatalog::SYNC_OBJECT_NAME));
	
	// 静态对象
	static LogCatalog logcatalog;
	static LogMsgDispatcher distpatcher;
	logcatalog.msgDispatcher_ = &distpatcher;

	return &logcatalog;
}

// constructor and destructors
LogCatalog::LogCatalog(void) {
}

LogCatalog::~LogCatalog(void) {
	using namespace SyncObjects;
	SyncObject::Destroy(LogCatalog::SYNC_OBJECT_NAME);
}

Logger * LogCatalog::getLogger(const std::string &logger_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogCatalog::SYNC_OBJECT_NAME));

	LOGGER_MAP::const_iterator iter = logger_map_.find(logger_name);
	if (iter != logger_map_.end())
		return iter->second;
	else 
		return NULL;
}
Logger * LogCatalog::createLogger(const std::string &logger_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogCatalog::SYNC_OBJECT_NAME));

	try {
		LOGGER_MAP::const_iterator iter = logger_map_.find(logger_name);
		if (iter == logger_map_.end()) {
			Logger * logger = new Logger(logger_name, msgDispatcher_);
			logger_map_.insert(std::make_pair(logger_name, logger));
			return logger;
		} else {
			return iter->second;
		}
	} catch (std::bad_alloc &) {
		return NULL;
	}
}

void LogCatalog::Destroy(const std::string &loggername) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogCatalog::SYNC_OBJECT_NAME));

	LOGGER_MAP::iterator iter = logger_map_.find(loggername);
	if (iter != logger_map_.end()) {
		delete iter->second;
		logger_map_.erase(iter);
	}
}
void LogCatalog::DestroyAll() {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogCatalog::SYNC_OBJECT_NAME));

	LOGGER_MAP::iterator iter = logger_map_.begin();
	for (; iter != logger_map_.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
	logger_map_.clear();
}

};