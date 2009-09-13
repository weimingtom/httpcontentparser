#include "StdAfx.h"
#include ".\dnsmaptest.h"
#include "..\..\projects\PacketsGrasper\DNSMap.h"
#include <string>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;
using namespace std;


void TestDNSMap() {
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

	BOOST_CHECK(dns1 == dnsmap.get(data1));
	BOOST_CHECK(dns2 == dnsmap.get(data2));
	BOOST_CHECK(dns3 == dnsmap.get(data3));
	BOOST_CHECK(dns4 == dnsmap.get(data4));

	// 测试一个不存在的
	int datax = 1010;
	BOOST_CHECK(dnsmap.get(datax) == "");

	// remove
	dnsmap.remove(data1);
	BOOST_CHECK(dnsmap.get(data1) == "");
}