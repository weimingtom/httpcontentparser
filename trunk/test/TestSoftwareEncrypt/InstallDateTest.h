#ifndef _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__
#define _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__

#include "stdafx.h"
#include <windows.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void TestInstallDateItem();
void TestGetInstallDateFromRegistry();
void TestGetInstallDateFromFile();
void TestGetInstallDateFromWin();


SYSTEMTIME st_from_tm(const tm &t);

#endif  // _TEST_SOFTWAREENCRYPT_INSTALLDATETEST_H__