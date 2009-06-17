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

	// 启用"仅仅通过白名单之后"
	dns_setting.justPassWhiteDNS(true);

	SettingItem::setModified(false);
	CPPUNIT_ASSERT(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.163.com"));
	CPPUNIT_ASSERT(false == SettingItem::isModified());

	// 如果"白名单检测"不可用，那么"仅仅通过白名单"的功能也将不可用
	dns_setting.enableWhiteDNSCheck(false);
	CPPUNIT_ASSERT(true  ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	CPPUNIT_ASSERT(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	CPPUNIT_ASSERT(true == dns_setting.fuzzeCheckDNS("p1.163.com"));

	// 回复状态
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

	// 当已经在黑名单加入，就不能在白名单加入，反之亦然
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