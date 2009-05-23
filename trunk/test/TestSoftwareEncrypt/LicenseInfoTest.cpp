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
		// ʹ��һ���Ƿ���SN�� ȷ��������δע��״̬
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
		// ʹ��һ���Ƿ���SN�� ȷ��������δע��״̬
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
		// ��ʼʱʹ��һ���Ϸ���ע���룬 �ú�ʹ�÷Ƿ���ע��
		// ����Ӧ��ʼ�ձ�����ע���״̬
		// ʹ��һ���Ƿ���SN�� ȷ��������δע��״̬
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