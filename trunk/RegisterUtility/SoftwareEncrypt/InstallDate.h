#ifndef _SOFTWARE_ENCRYPT_INSTALLDATE_H__
#define _SOFTWARE_ENCRYPT_INSTALLDATE_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define INSTALL_DAYS_ERROR	0xFFFFFFFF

// 获取安装时间
class InstallDate {
public:
	InstallDate(void);
	~InstallDate(void);

public:
	unsigned int  getInstalledDays(); // 获取安装的天数
	
	// 为第一次安装准备
	int setInstall();

	std::string getInstallData();
};

#endif  // _SOFTWARE_ENCRYPT_INSTALLDATE_H__