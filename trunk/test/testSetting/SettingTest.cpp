#include "StdAfx.h"
#include ".\settingtest.h"
#include <Globalsetting.h>
#include <string>

using namespace std;
using namespace CPPUNIT_NS;

void SettingTest::setUp() {
}

void SettingTest::tearDown() {
}


//===================================
// Tests

void SettingTest::CheckBlackDNSTest() {
	const string dns_name = "www.sina.com";
	const string dns_name1 = "www.sohu.com";

	GlobalSetting globalsetting;
	globalsetting.initialize();

	// δ���DNS֮ǰ
	globalsetting.enableDNSCheck(false);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name1));
	globalsetting.enableDNSCheck(true);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name1));
	
	// ���DNS
	globalsetting.addBlackDNS(dns_name);
	globalsetting.enableDNSCheck(true);
	CPPUNIT_ASSERT(false == globalsetting.checkDNS(dns_name));
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name1));
	globalsetting.enableDNSCheck(false);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name1));

	// ��DNS�Ƴ�֮��
	globalsetting.removeBlackDNS(dns_name);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
	globalsetting.enableDNSCheck(true);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
	globalsetting.enableDNSCheck(false);
	CPPUNIT_ASSERT(true == globalsetting.checkDNS(dns_name));
}

void SettingTest::CheckIPTest() {
	// ��ʼ��
	GlobalSetting globalsetting;
	globalsetting.initialize();

	// ���DNS
	const string dns_name = "www.sina.com";
	globalsetting.enableDNSCheck(true);
	globalsetting.addBlackDNS(dns_name);


	const string ip1 = "71.5.7.191", ip2 = "18.29.38.17";// ip2Ϊ����ip
	CPPUNIT_ASSERT(false == globalsetting.checkIP(ip1));
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip2));

	// ͣ��DNS����
	globalsetting.enableDNSCheck(false);
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip1));
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip2));

	// �ٴ�����
	globalsetting.enableDNSCheck(true);
	CPPUNIT_ASSERT(false == globalsetting.checkIP(ip1));
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip2));

	// �Ƴ���
	globalsetting.removeBlackDNS(dns_name);
	globalsetting.enableDNSCheck(true);
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip1));
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip2));
	globalsetting.enableDNSCheck(false);
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip1));
	CPPUNIT_ASSERT(true == globalsetting.checkIP(ip2));

}