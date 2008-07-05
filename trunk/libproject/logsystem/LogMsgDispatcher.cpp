#include "precomp.h"
#include ".\logmsgdispatcher.h"
#include "logcatalog.h"
#include ".\loglistener.h"
#include "logger.h"

#include <vector>
#include <assert.h>
#include <map>
#include <string>

namespace LogSystem {

const std::string LogMsgDispatcher::SYNC_OBJECT_NAME = "LogSystem::LogMsgDispatcher";

LogMsgDispatcher::LogMsgDispatcher(void)
{
}

LogMsgDispatcher::~LogMsgDispatcher(void)
{
}

void LogMsgDispatcher::RegisterListener(const std::string &logger_name,
										const std::string &listener_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogMsgDispatcher::SYNC_OBJECT_NAME));

	message_register_map_.insert(
		std::make_pair<std::string, std::string>(logger_name, listener_name));
}

void LogMsgDispatcher::UnRegisterListener(const std::string &logger_name,
										  const std::string &listener_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogMsgDispatcher::SYNC_OBJECT_NAME));

	MESSAGE_RECV_MAP::iterator iter = message_register_map_.lower_bound(logger_name);
	MESSAGE_RECV_MAP::const_iterator iterEnd = message_register_map_.upper_bound(logger_name);
	for (; iter != iterEnd; ++iter) {
		if (iter->second == listener_name) {
			message_register_map_.erase(iter);
			break;
		}
	}
} 
void LogMsgDispatcher::SendMessage(const std::string &logger_name, const char *msg,
								   const int len) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		LogMsgDispatcher::SYNC_OBJECT_NAME));

	MESSAGE_RECV_MAP::iterator iter = message_register_map_.lower_bound(logger_name);
	MESSAGE_RECV_MAP::iterator iterEnd = message_register_map_.upper_bound(logger_name);

	// 如果有一些listener已经被删除，那么把这些<logger, listener>记录在这里
	// 在消息发送完成后，删除这些
	// 注意， 我们不能在map枚举时，删除其中的任何一个元素
	// 因此采用了这种先记录，后删除的方式
	typedef std::vector<MESSAGE_RECV_MAP::iterator> ITERS_TO_DELETE;
	ITERS_TO_DELETE vec_iter_to_delete;

	Logger *logger =  LogCatalog::getInstance()->createLogger(logger_name);
	for (; iter != iterEnd; ++iter) {
		LogListener * listener = ListenerContainer::getInstance()->getListener(iter->second);
		if (listener != NULL) {
			listener->UpdateMessage(msg, len);
		} else {
			vec_iter_to_delete.push_back(iter);
		}
	}

	// 删除所有已经被移除的监听对
	ITERS_TO_DELETE::iterator iter_vec = vec_iter_to_delete.begin();
	for (; iter_vec != vec_iter_to_delete.end(); ++iter_vec) {
		message_register_map_.erase(*iter_vec);
	}
}

};