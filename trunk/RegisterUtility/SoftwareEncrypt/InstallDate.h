#ifndef _SOFTWARE_ENCRYPT_INSTALLDATE_H__
#define _SOFTWARE_ENCRYPT_INSTALLDATE_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define INSTALL_DAYS_ERROR	0xFFFFFFFF

// ��ȡ��װʱ��
class InstallDate {
public:
	InstallDate(void);
	~InstallDate(void);

public:
	unsigned int  getInstalledDays(); // ��ȡ��װ������
	
	// Ϊ��һ�ΰ�װ׼��
	int setInstall();

	std::string getInstallData();
};

#endif  // _SOFTWARE_ENCRYPT_INSTALLDATE_H__