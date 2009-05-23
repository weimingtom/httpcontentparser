#include "StdAfx.h"
#include ".\licenseinfotest.h"
#include <softwareEncrypt\serialNumber.h>
#include <softwareEncrypt\LicenseInfo.h>
#include <string>

LicenseInfoTest::LicenseInfoTest(void)
{
}

LicenseInfoTest::~LicenseInfoTest(void)
{
}

void LicenseInfoTest::testSNStored() {
	using namespace software_encrypt;
	using namespace std;

	string sn1 = "aaa23infadhf-2u3nfad", sne1;
	storeSN(sn1);
	sne1 = getSN();
	CPPUNIT_ASSERT(sn1 == sne1);

}