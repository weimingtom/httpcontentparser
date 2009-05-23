#include "StdAfx.h"
#include ".\licenseinfotest.h"
#include <softwareEncrypt\serialNumber.h>
#include <softwareEncrypt\LicenseInfo.h>
#include <softwareEncrypt\baseEncrypt.h>
#include <softwareStatus.h>
#include <string>

LicenseInfoTest::LicenseInfoTest(void) {
}

LicenseInfoTest::~LicenseInfoTest(void) {
}

void LicenseInfoTest::testSNStored() {
	using namespace software_encrypt;
	using namespace std;

	string sn1 = "aaa23infadhf-2u3nfad", sne1;
	storeSN(sn1);
	sne1 = getSN();
	CPPUNIT_ASSERT(sn1 == sne1);
}

void LicenseInfoTest::testReg() {
	using namespace software_encrypt;
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