#ifndef _LOGSYSTEM_LOG_FILE_LOG_LISTENER_H__
#define _LOGSYSTEM_LOG_FILE_LOG_LISTENER_H__

#include "LogListener.h"
#include <string> 
#include <fstream>
#include <ios>

// 此类可以将Log写入到文件当中
// 设计问题： 对于一些对象他们使用的文件可能相同
// 我们如何保证使用一个LogListener对象呢？


namespace LogSystem {


class FileLogListener : public LogListener {
public:
	FileLogListener(const std::string &filename, const std::string &name);
	~FileLogListener(void);

	virtual void UpdateMessage(const TCHAR *msg, const int len);
private:
	std::string filename_;
	std::fstream file_;
};
};

#endif  // _LOGSYSTEM_LOG_FILE_LOG_LISTENER_H__