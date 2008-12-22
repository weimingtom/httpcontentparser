#ifndef _SELECTIO_HOSTNAMERECORDER_H__
#define _SELECTIO_HOSTNAMERECORDER_H__

#include <string>
#include <map>
#include <set>

#define HOSTNAME_RECORD_BUFFER_SIZE  10

// class HostnameRecorder
// 用于记录主机名称
class HostnameRecorder {
public:
	HostnameRecorder(void);
	~HostnameRecorder(void);

public:
	void flush();
	void add(std::string &hostname);
	
private:
	typedef std::set<std::string> HOSTNAME_SET;
	HOSTNAME_SET host_name;
	TCHAR install_path[MAX_PATH];

	void getInstallPath();
};

#endif  // _SELECTIO_HOSTNAMERECORDER_H__
