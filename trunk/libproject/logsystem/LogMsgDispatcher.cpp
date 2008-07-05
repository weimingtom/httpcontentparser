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

	// �����һЩlistener�Ѿ���ɾ������ô����Щ<logger, listener>��¼������
	// ����Ϣ������ɺ�ɾ����Щ
	// ע�⣬ ���ǲ�����mapö��ʱ��ɾ�����е��κ�һ��Ԫ��
	// ��˲����������ȼ�¼����ɾ���ķ�ʽ
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

	// ɾ�������Ѿ����Ƴ��ļ�����
	ITERS_TO_DELETE::iterator iter_vec = vec_iter_to_delete.begin();
	for (; iter_vec != vec_iter_to_delete.end(); ++iter_vec) {
		message_register_map_.erase(*iter_vec);
	}
}

};