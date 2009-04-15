#ifndef _SOFTWARE_ENCRYPT_INSTALLDATE_H__
#define _SOFTWARE_ENCRYPT_INSTALLDATE_H__

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace software_encrypt{

const int  INSTALL_DAYS_ERROR	 = 0xFFFFFFFF;

int setInstall();
std::string getInstallData();
unsigned int  getInstalledDays(); // ��ȡ��װ������

void setInstallDataOnRegistry(const FILETIME &ft);
void setInstallDateFile(const FILETIME &ft);
void setInstallDateInWin(const FILETIME &ft);

boost::posix_time::ptime getInstallDateFromRegistry() ;
boost::posix_time::ptime getInstallDateFromFile() ;
boost::posix_time::ptime getInstallDateFromWin() ;
boost::posix_time::ptime getInstallDataTime();

};

#endif  // _SOFTWARE_ENCRYPT_INSTALLDATE_H__