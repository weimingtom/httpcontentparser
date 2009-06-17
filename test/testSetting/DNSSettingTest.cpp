#include "StdAfx.h"
#include ".\dnssettingtest.h"
#include <DNSSetting.h>
using namespace CPPUNIT_NS;

DNSSettingTest::DNSSettingTest(void) {
}

DNSSettingTest::~DNSSettingTest(void) {
}

void DNSSettingTest::testJustPassedWhiteDNS() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	SettingItem::setModified(false);
	CPPUNIT_ASSERT(true == dns_setting.addBlackDNS("sina.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addBlackDNS("sohu.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addWhiteDNS("google.com"));
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	SettingItem::setModified(false);
	dns_setting.enableBlackDNSCheck(true);
	CPPUNIT_ASSERT( true == SettingItem::isModified());
	
	SettingItem::setModified(false);
	dns_setting.enableWhiteDNSCheck(true);
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	SettingItem::setModified(false);
	dns_setting.justPassWhiteDNS(false);
	CPPUNIT_ASSERT( true == SettingItem::isModified());

	SettingItem::setModified(false);
	CPPUNIT_ASSERT(true  ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.163.com"));
	CPPUNIT_ASSERT(false == SettingItem::isModified());

	// ����"����ͨ��������֮��"
	dns_setting.justPassWhiteDNS(true);

	SettingItem::setModified(false);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.163.com"));
	CPPUNIT_ASSERT(false == SettingItem::isModified());

	// ���"���������"�����ã���ô"����ͨ��������"�Ĺ���Ҳ��������
	dns_setting.enableWhiteDNSCheck(false);
	CPPUNIT_ASSERT(true  ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.163.com"));

	// �ظ�״̬
	dns_setting.enableWhiteDNSCheck(true);
	dns_setting.justPassWhiteDNS(true);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("news.sina.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.163.com"));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.163.com"));

	dns_setting.justPassWhiteDNS(false);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.163.com"));
}

void DNSSettingTest::testTwoModels() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	CPPUNIT_ASSERT(true == dns_setting.addBlackDNS("sina.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addBlackDNS("sohu.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addWhiteDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	
	SettingItem::setModel(SettingItem::MODE_PARENT);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
}

void DNSSettingTest::testFuzzeCheck() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	CPPUNIT_ASSERT(true == dns_setting.addBlackDNS("sina.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addBlackDNS("sohu.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addWhiteDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));

	dns_setting.enableBlackDNSCheck(false);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
}

void DNSSettingTest::testCheck() {
	CPPUNIT_ASSERT(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	CPPUNIT_ASSERT(true == dns_setting.addBlackDNS("sina.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addBlackDNS("sohu.com"));
	CPPUNIT_ASSERT(true ==  dns_setting.addWhiteDNS("google.com"));

	// ���Ѿ��ں��������룬�Ͳ����ڰ��������룬��֮��Ȼ
	CPPUNIT_ASSERT(false ==   dns_setting.addWhiteDNS("sina.com"));
	CPPUNIT_ASSERT(false == dns_setting.addWhiteDNS("sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.addBlackDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	CPPUNIT_ASSERT(true == dns_setting.checkDNS("google.com"));
	CPPUNIT_ASSERT(false == dns_setting.checkDNS("sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.checkDNS("sohu.com"));


	dns_setting.enableBlackDNSCheck(false);
	CPPUNIT_ASSERT(true == dns_setting.checkDNS("google.com"));
	CPPUNIT_ASSERT(true == dns_setting.checkDNS("sohu.com"));
	CPPUNIT_ASSERT(true == dns_setting.checkDNS("sohu.com"));
}