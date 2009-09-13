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
#include <boost\test\test_tools.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::unit_test;

namespace {
	// ��ȡ��ǰ����ǰdays�����ڵ�FILETIME
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



void testInstallDate() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	FILETIME ft;
	SYSTEMTIME st;

	//test 1
	// �Ƿ�ע���룬 �ҳ�����������
	{
	// ����ע����
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// ���ð�װʱ��
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
	BOOST_CHECK(ii.registered() == false);
	BOOST_CHECK(ii.getAppStatus() == SNOWMAN_STATUS_OVERTIME);
	}

	// �Ϸ���
	{
	storeSN(generateSN());
	// ���ð�װʱ��
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
	BOOST_CHECK(ii.registered() == true);
	BOOST_CHECK(ii.getAppStatus() == SNOWMAN_STATUS_REGISTERED);
	}

	// �������ڵ�
	{
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// ���ð�װʱ��
	FILETIME ft = get_ft_before_days(5);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	int a = ii.getInstallDays();
	BOOST_CHECK(ii.registered() == false);
	BOOST_CHECK(ii.getInstallDays() == 5);
	BOOST_CHECK(ii.getAppStatus() == SNOWMAN_STATUS_TRIAL);
	
	}

	// ���������
	{
	string sn = "aaa23infadhf-2u3nfad";
	storeSN(sn);
	// ���ð�װʱ��
	FILETIME ft = get_ft_before_days(REG_SOFTWARE_TRAIL_DAYES + 3);
	internal_utility::setInstallDateFile(ft);
	internal_utility::setInstallDataOnRegistry(ft);
	internal_utility::setInstallDateInWin(ft);


	LicenseInfo ii;
	ii.initialize();
	BOOST_CHECK(ii.registered() == false);
	BOOST_CHECK(ii.getAppStatus() == SNOWMAN_STATUS_OVERTIME);
	BOOST_CHECK(ii.getDaysLeft() < 0);
	BOOST_CHECK(ii.getInstallDays() == REG_SOFTWARE_TRAIL_DAYES+3) ;
	}
}

void testSNStored() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	string sn1 = "aaa23infadhf-2u3nfad", sne1;
	storeSN(sn1);
	sne1 = getSN();
	BOOST_CHECK(sn1 == sne1);
}

void testReg() {
	using namespace software_encrypt;
	using namespace software_encrypt::internal_utility;
	using namespace std;

	{
		// ʹ��һ���Ƿ���SN�� ȷ��������δע��״̬
		string sn1 = "aaa23infadhf-2u3nfad", sne1;
		string sn2 = generateSN();
		storeSN(sn1);
		LicenseInfo ii;
		ii.initialize();
		BOOST_CHECK(false == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());
		ii.regApp(sn1);
		BOOST_CHECK(false == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());
		ii.regApp(sn2);
		BOOST_CHECK(true == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());

	}

	{
		// ʹ��һ���Ƿ���SN�� ȷ��������δע��״̬
		string sn1 = "aaa23infadhf-2u3nfad", sne1;
		storeSN(sn1);
		LicenseInfo ii;
		ii.initialize();
		BOOST_CHECK(false == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED != ii.getAppStatus());

		std::string sn = generateSN();
		storeSN(sn);
		LicenseInfo ii2;
		ii2.initialize();
		BOOST_CHECK(true == ii2.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED == ii2.getAppStatus());
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
		BOOST_CHECK(true == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());
		ii.regApp(sn1);
		BOOST_CHECK(true == ii.registered());
		BOOST_CHECK(SNOWMAN_STATUS_REGISTERED == ii.getAppStatus());
	}
}