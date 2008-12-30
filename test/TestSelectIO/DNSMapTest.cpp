#include "StdAfx.h"
#include ".\dnsmaptest.h"
#include <DNSMap.h>
#include <string>

using namespace std;

DNSMapTest::DNSMapTest(void) {
}

DNSMapTest::~DNSMapTest(void) {
}

void DNSMapTest::TestDNSMap() {
	DNSMap dnsmap;

	int data1 = 1;
	string dns1 = "google";
	dnsmap.add(data1, dns1);
	dnsmap.add(data1, dns1);
	dnsmap.add(data1, dns1);

	int data2 = 2;
	string dns2 = "sina";
	dnsmap.add(data1, dns1);

	int data3 = 3;
	string dns3 = "baidu";
	dnsmap.add(data1, dns1);

	int data4 = 4;
	string dns4 = "sohu";
	dnsmap.add(data1, dns1);

	CPPUNIT_ASSERT(dns1 == dnsmap.get(data1));
	CPPUNIT_ASSERT(dns2 == dnsmap.get(data2));
	CPPUNIT_ASSERT(dns3 == dnsmap.get(data3));
	CPPUNIT_ASSERT(dns4 == dnsmap.get(data4));

	// 测试一个不存在的
	int datax = 1010;
	CPPUNIT_ASSERT(dnsmap.get(datax) == "");

	// remove
	dnsmap.remove(data1);
	CPPUNIT_ASSERT(dnsmap.get(data1) == "");
}