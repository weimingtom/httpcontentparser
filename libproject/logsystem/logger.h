#ifndef _LOGSYSTEM_LOG_LOGGER_H__
#define _LOGSYSTEM_LOG_LOGGER_H__

#include <vector>
#include <string>

namespace LogSystem {

class LogCatalog;
class LogMsgDispatcher;
class LogListener;

class Logger {
public:
	~Logger(void);

	void write(const char * log_content, const int len);
	void append(const char * log_content, const int len);
	const std::string & getName() { return logger_name_;}

	bool isEnable() const { return enable_log_;}
	void Enable(bool bEnable) { enable_log_ = bEnable; }
	void AddListener(LogListener *listener);
	void RemoveListener(LogListener *listener);
private:
	const std::string logger_name_;

	// ����ת����Ϣ
	LogMsgDispatcher *msgDispatcher_;

	bool enable_log_;

	// ���е�Logger����LogCatalog����
	friend class LogCatalog;
	Logger();
	Logger(const std::string &loggername,
		 LogMsgDispatcher *dispatcher);

	// ͬ����������
	static const std::string SYNC_OBJECT_NAME;
};

};

#endif  // _LOGSYSTEM_LOG_LOGGER_H__