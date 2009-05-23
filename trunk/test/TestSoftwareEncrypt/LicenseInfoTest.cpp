#include "StdAfx.h"
#include ".\licenseinfotest.h"
#include ".\installdatetest.h"
#include <softwareEncrypt\serialNumber.h>
#include <softwareEncrypt\LicenseInfo.h>
#include <softwareEncrypt\baseEncrypt.h>
#include <softwareencrypt\installdate.h>
#include <softwareStatus.h>
#include <app_constants.h>
#include <string>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace {
	// 获取当前日期前days的日期的FILETIME
	FILETIME get_ft_before_days(const int dd) {
		using namespace boost::posix_time;
		ptime p = second_clock::local_time();
		p = p - boost::gregorian::days(dd);
		tm t =	to_tm(p);
		FILETIME ft;
		SYSTEMTIME st = st_from_tm(t);
		SystemTimeToFileTime(&st, &ft);
		return ft;
	}
}

LicenseInfoTest::LicenseInfoTest(void) {
	rawSN1 = software_encrypt::internal_utility::getSN();
	rawdate = software_encrypt::getInstallDataTime();
}

LicenseInfoTest::~LicenseInfoTest(void) {
	software_encrypt::internal_utility::storeSN(rawSN1);

	tm t =	to_tm(rawdate);
	FILETIME ft;
	SYSTEMTIME st = st_from_tm(t);
	SystemTimeToFileTime(&st, &ft);
	software_encrypt::internal_utility::setInstallDateFile(ft);
	software_encrypt::internal_utility::setInstallDataOnRegistry(ft);
	software_encrypt::internal_utility::setInstallDateInWin(ft);
}

void LicenseInfoTest::testInstallDate() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	FILETIME ft;
	SYSTEMTIME st;

	//test 1
	// 非法注册码， 且超过了试用期
	{
	// 设置注册码
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// 设置安装时间
	memset(&st, 0, sizeof(st));
	st.wYear = 2008;
	st.wMonth = 5;
	st.wDay = 8;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	CPPUNIT_ASSERT(ii.registered() == false);
	CPPUNIT_ASSERT(ii.getAppStatus() == SNOWMAN_STATUS_OVERTIME);
	}

	// 合法的
	{
	storeSN(generateSN());
	// 设置安装时间
	memset(&st, 0, sizeof(st));
	st.wYear = 2008;
	st.wMonth = 5;
	st.wDay = 8;
	SystemTimeToFileTime(&st, &ft);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	CPPUNIT_ASSERT(ii.registered() == true);
	CPPUNIT_ASSERT(ii.getAppStatus() == SNOWMAN_STATUS_REGISTERED);
	}

	// 试用期内的
	{
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// 设置安装时间
	FILETIME ft = get_ft_before_days(5);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	int a = ii.getInstallDays();
	CPPUNIT_ASSERT(ii.registered() == false);
	CPPUNIT_ASSERT(ii.getInstallDays() == 5);
	CPPUNIT_ASSERT(ii.getAppStatus() == SNOWMAN_STATUS_TRIAL);
	
	}

	// 试用期外的
	{
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// 设置安装时间
	FILETIME ft = get_ft_before_days(REG_SOFTWARE_TRAIL_DAYES + 3);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	CPPUNIT_ASSERT(ii.registered() == false);
	CPPUNIT_ASSERT(ii.getAppStatus() == SNOWMAN_STATUS_OVERTIME);
	CPPUNIT_ASSERT(ii.getDaysLeft() < 0);
	CPPUNIT_ASSERT(ii.getInstallDays() == REG_SOFTWARE_TRAIL_DAYES+3) ;
	}
}

void LicenseInfoTest::testSNStored() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	string sn1 = "aaa23infadhf-2u3nfad", sne1;
	storeSN(sn1);
	sne1 = getSN();
	CPPUNIT_ASSERT(sn1 == sne1);
}

void LicenseInfoTest::testReg() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	{
		// 使用一个非法的SN， 确保程序处于未注册状态
		string sn1 = "aaa23infadhf-2u3nfad", sne1;
		string sn2 = generateSN();
		storeSN(sn1);
		LicenseInfo ii;
		ii.initialize();
		CPPUNIT_ASSERT(false == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());
		ii.regApp(sn1);
		CPPUNIT_ASSERT(false == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());
		ii.regApp(sn2);
		CPPUNIT_ASSERT(true == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());

	}

	{
		// 使用一个非法的SN， 确保程序处于未注册状态
		string sn1 = "aaa23infadhf-2u3nfad", sne1;
		storeSN(sn1);
		LicenseInfo ii;
		ii.initialize();
		CPPUNIT_ASSERT(false == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());

		std::string sn = generateSN();
		storeSN(sn);
		LicenseInfo ii2;
		ii2.initialize();
		CPPUNIT_ASSERT(true == ii2.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED == ii2.getAppStatus());
	}

	{
		// 开始时使用一个合法的注册码， 让后使用非法的注册
		// 程序应该始终保持在注册的状态
		// 使用一个非法的SN， 确保程序处于未注册状态
		string sn1 = "aaa23infadhf-2u3nfad";
		string sn2 = generateSN();
		storeSN(sn2);
		LicenseInfo ii;
		ii.initialize();
		CPPUNIT_ASSERT(true == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());
		ii.regApp(sn1);
		CPPUNIT_ASSERT(true == ii.registered());
		CPPUNIT_ASSERT(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());
	}
}