#ifndef _LOGSYSTEM_LOG_FILE_LOG_LISTENER_H__
#define _LOGSYSTEM_LOG_FILE_LOG_LISTENER_H__

#include "LogListener.h"
#include <string> 
#include <fstream>
#include <ios>

// ������Խ�Logд�뵽�ļ�����
// ������⣺ ����һЩ��������ʹ�õ��ļ�������ͬ
// ������α�֤ʹ��һ��LogListener�����أ�


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