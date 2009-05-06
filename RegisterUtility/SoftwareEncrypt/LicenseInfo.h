#ifndef _SOFTWARE_ENCRYPT_LICENSEINFO_H__
#define _SOFTWARE_ENCRYPT_LICENSEINFO_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace software_encrypt {

const int MAX_DAYS = 0xFFFFFFFF;

class LicenseInfo {
public:
	LicenseInfo(void);
	~LicenseInfo(void);

public:
	int getInstallDays();	// 获取时间期限
	int getDaysLeft();	// 剩余多少天使用
	bool registered(); // 是否已经注册了

	void initialize();		// 初始化
	bool regApp(const std::string &bstr);
	int getAppStatus();
private:
	//======================
	// 一下信息都应该只从文件中读取一次
	// 尽量减少次数，有利于防止“记录时间"的地点被发现
	// 安装日期
	boost::posix_time::ptime install_time_;

	// 序列号
	std::string sn_;

	// 用于调试
	bool initialized_;
};

};

#endif  // _SOFTWARE_ENCRYPT_LICENSEINFO_H__