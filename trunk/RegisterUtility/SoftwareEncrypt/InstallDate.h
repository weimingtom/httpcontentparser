#ifndef _SOFTWARE_ENCRYPT_INSTALLDATE_H__
#define _SOFTWARE_ENCRYPT_INSTALLDATE_H__

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
#include <windows.h>

namespace software_encrypt {

const int  INSTALL_DAYS_ERROR	 = 0xFFFFFFFF;

int setInstall();
std::string getInstallData();
unsigned int  getInstalledDays(); // ��ȡ��װ������
boost::posix_time::ptime getInstallDataTime();

namespace internal_utility {
	void setInstallDataOnRegistry(const FILETIME &ft);
	void setInstallDateFile(const FILETIME &ft);
	void setInstallDateInWin(const FILETIME &ft);

	boost::posix_time::ptime getInstallDateFromRegistry() ;
	boost::posix_time::ptime getInstallDateFromFile() ;
	boost::posix_time::ptime getInstallDateFromWin() ;	
}
};

#endif  // _SOFTWARE_ENCRYPT_INSTALLDATE_H__