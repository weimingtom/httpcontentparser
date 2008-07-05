#include "precomp.h"
#include ".\logger.h"
#include ".\logmsgdispatcher.h"
#include ".\loglistener.h"

#include <assert.h>

namespace LogSystem {

const std::string	Logger::SYNC_OBJECT_NAME = "LogSystem::Logger";

Logger::Logger(const std::string &loggername,
			   LogMsgDispatcher *dispatcher) :
			logger_name_(loggername), 
			msgDispatcher_(dispatcher) {
	enable_log_ = true;

	// 创建同步对象
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		Logger::SYNC_OBJECT_NAME));
}
Logger::Logger() {
	// 此构造函数不应被调用
	assert(false);
}
Logger::~Logger(void) {
	using namespace SyncObjects;
	SyncObject::Destroy(Logger::SYNC_OBJECT_NAME);
}
void Logger::append(const char * log_content, const int len) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		Logger::SYNC_OBJECT_NAME));

	if (enable_log_ == true) {
		msgDispatcher_->SendMessage(getName(), log_content, len);
	}
}

void Logger::write(const char * log_content, const int  len) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		Logger::SYNC_OBJECT_NAME));

	if (enable_log_ == true) {
		msgDispatcher_->SendMessage(getName(), log_content, len);
	}
}

void Logger::AddListener(LogListener *listener) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		Logger::SYNC_OBJECT_NAME));

	// 由类LogMsgDispatcher负责所有消息的转发
	msgDispatcher_->RegisterListener(getName(), listener->getName());
}

void Logger::RemoveListener(LogListener *listener) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		Logger::SYNC_OBJECT_NAME));

	msgDispatcher_->UnRegisterListener(getName(), listener->getName());
}

};