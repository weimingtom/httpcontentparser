#include "StdAfx.h"
#include ".\dnssettingtest.h"
#include <setting\DNSSetting.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

void testJustPassedWhiteDNS() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	SettingItem::setModified(false);
	BOOST_CHECK(true == dns_setting.addBlackDNS("sina.com"));
	BOOST_CHECK(true ==  dns_setting.addBlackDNS("sohu.com"));
	BOOST_CHECK(true ==  dns_setting.addWhiteDNS("google.com"));
	BOOST_CHECK( true == SettingItem::isModified());

	SettingItem::setModified(false);
	dns_setting.enableBlackDNSCheck(true);
	BOOST_CHECK( true == SettingItem::isModified());
	
	SettingItem::setModified(false);
	dns_setting.enableWhiteDNSCheck(true);
	BOOST_CHECK( true == SettingItem::isModified());

	SettingItem::setModified(false);
	dns_setting.justPassWhiteDNS(false);
	BOOST_CHECK( true == SettingItem::isModified());

	SettingItem::setModified(false);
	BOOST_CHECK(true  ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.163.com"));
	BOOST_CHECK(false == SettingItem::isModified());

	// ����"����ͨ��������֮��"
	dns_setting.justPassWhiteDNS(true);

	SettingItem::setModified(false);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.163.com"));
	BOOST_CHECK(false == SettingItem::isModified());

	// ���"���������"�����ã���ô"����ͨ��������"�Ĺ���Ҳ��������
	dns_setting.enableWhiteDNSCheck(false);
	BOOST_CHECK(true  ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.163.com"));

	// �ظ�״̬
	dns_setting.enableWhiteDNSCheck(true);
	dns_setting.justPassWhiteDNS(true);

	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("news.sina.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.163.com"));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.163.com"));

	dns_setting.justPassWhiteDNS(false);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sina.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.csdn.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.163.com"));
}

void testTwoModels() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	BOOST_CHECK(true == dns_setting.addBlackDNS("sina.com"));
	BOOST_CHECK(true ==  dns_setting.addBlackDNS("sohu.com"));
	BOOST_CHECK(true ==  dns_setting.addWhiteDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
	
	SettingItem::setModel(SettingItem::MODE_PARENT);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));

	SettingItem::setModel(SettingItem::MODE_CHILD);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
}

void testFuzzeCheck() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	BOOST_CHECK(true == dns_setting.addBlackDNS("sina.com"));
	BOOST_CHECK(true ==  dns_setting.addBlackDNS("sohu.com"));
	BOOST_CHECK(true ==  dns_setting.addWhiteDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(false == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));

	dns_setting.enableBlackDNSCheck(false);
	BOOST_CHECK(true ==  dns_setting.fuzzeCheckDNS("name.google.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("news.sohu.com"));
	BOOST_CHECK(true == dns_setting.fuzzeCheckDNS("p1.sine.sina.com"));
}

void testCheck() {
	BOOST_CHECK(SettingItem::MODE_CHILD == SettingItem::getModel());

	DNSList black(""), white("");
	DNSSetting dns_setting;
	dns_setting.initialize(&black, &white);

	BOOST_CHECK(true == dns_setting.addBlackDNS("sina.com"));
	BOOST_CHECK(true ==  dns_setting.addBlackDNS("sohu.com"));
	BOOST_CHECK(true ==  dns_setting.addWhiteDNS("google.com"));

	// ���Ѿ��ں��������룬�Ͳ����ڰ��������룬��֮��Ȼ
	BOOST_CHECK(false ==   dns_setting.addWhiteDNS("sina.com"));
	BOOST_CHECK(false == dns_setting.addWhiteDNS("sohu.com"));
	BOOST_CHECK(false == dns_setting.addBlackDNS("google.com"));

	dns_setting.enableBlackDNSCheck(true);
	BOOST_CHECK(true == dns_setting.checkDNS("google.com"));
	BOOST_CHECK(false == dns_setting.checkDNS("sohu.com"));
	BOOST_CHECK(false == dns_setting.checkDNS("sohu.com"));


	dns_setting.enableBlackDNSCheck(false);
	BOOST_CHECK(true == dns_setting.checkDNS("google.com"));
	BOOST_CHECK(true == dns_setting.checkDNS("sohu.com"));
	BOOST_CHECK(true == dns_setting.checkDNS("sohu.com"));
}