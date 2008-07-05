#ifndef _LOGSYSTEM_LOG_CATALOG_H__
#define _LOGSYSTEM_LOG_CATALOG_H__

#include <string>
#include <map>

//namespace logststem {

namespace LogSystem {

class LogMsgDispatcher;
class Logger;

// ����log catalog, ������
class LogCatalog {
public:
	static LogCatalog * getInstance();

	Logger * getLogger(const std::string &logger_name);
	Logger * createLogger(const std::string &logger_name);
	void Destroy(const std::string &loggername);
	void DestroyAll();
	~LogCatalog(void);
private:
	// ͨ��getInstance��ȡʵ��
	typedef std::map< std::string, Logger* > LOGGER_MAP;
	static LOGGER_MAP logger_map_;
	LogCatalog(void);

	LogMsgDispatcher *msgDispatcher_;

	static const std::string SYNC_OBJECT_NAME;
};

};

#endif  // _LOGSYSTEM_LOG_CATALOG_H__
