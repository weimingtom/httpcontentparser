#ifndef _UTILITY_DNS_TEST_H__
#define _UTILITY_DNS_TEST_H__

#include <string>
#include <utility/dns.h>

// DNSTest
void TestGetMainServName();
void TestContainIPinDNS();
void TestValidateIPWithEnd();
void TestvalidateIP();
void GetMultHostName();
void GetDNS();
void GetMainNameWithPort();	// 测试带有端口号的地址
void GetMainNameTest();	
void BeginWWWTest();
void GetMainNameFromBrowseAddresss();
void GetMainNameFromBrowseAddressswithProto();


#endif  // _UTILITY_DNS_TEST_H__