#ifndef _SOFTWARE_ENCRYPT_INSTALLDATE_H__
#define _SOFTWARE_ENCRYPT_INSTALLDATE_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// 获取安装时间
class InstallDate {
public:
	InstallDate(void);
	~InstallDate(void);

public:
	int  getInstalledDays(); // 获取安装的天数
	
	// 为第一次安装准备
	int setInstall();
private:
	boost::posix_time::ptime getInstallDataTime();
	boost::posix_time::ptime getInstallDateFromRegistry();
	boost::posix_time::ptime getInstallDateFromFile();
	boost::posix_time::ptime getInstallDateFromWin();
};

#endif  // _SOFTWARE_ENCRYPT_INSTALLDATE_H__