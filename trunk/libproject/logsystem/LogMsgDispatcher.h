#pragma once

#include <map>

class LogListener;
class Logger;
class LogCatalog;

namespace LogSystem {

// 该类负责转发消息
class LogMsgDispatcher {
public:
	LogListener * CreateNewListener(const std::string &listener_type,
		const std::string &listener_name);
	void RegisterListener(const std::string &logger_name,
		const std::string &listener_name);

	void UnRegisterListener(const std::string &logger_name,
		const std::string &listener_name);

	void SendMessage(const std::string &logger_name, const char *msg, const int len) ;
private:
	friend class LogCatalog;

	typedef std::multimap<std::string, std::string>  MESSAGE_RECV_MAP;
	MESSAGE_RECV_MAP message_register_map_;

	LogMsgDispatcher(void);
	~LogMsgDispatcher(void);

	static const std::string SYNC_OBJECT_NAME;
};

};
