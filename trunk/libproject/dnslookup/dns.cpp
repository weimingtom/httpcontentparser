#include "stdafx.h"
#include "dns.h"
#include <tchar.h>
  

/////////////////////////////////////////////////////////////////////////////
// CDNS class
CDNS::CDNS() {
}
bool CDNS::doDNSLookup() {
	// Define host and socket structures
	WSADATA sockData;                           
	hostent *dnsInfo;                     

	// ³õÊ¼»¯Winsock
	if(WSAStartup(0x0101, &sockData) != 0) 	{
  		WSACleanup(); 
		return false;
	}

	dnsInfo = gethostbyname(hostName_.c_str());

	if(!dnsInfo) 	{
		WSACleanup();
		return false;
	}

	dnsIps_.clear();
	hostIps_.clear();

	for(int i = 0; dnsInfo->h_addr_list[i]; i++) 	{
		dnsIps_.push_back(inet_ntoa(*((struct in_addr *)dnsInfo->h_addr_list[i])));
	}

	if(dnsInfo->h_aliases[0]) 	{
   	 	for(i = 0; dnsInfo->h_aliases[i]; i++) 		{
			hostIps_.push_back(dnsInfo->h_aliases[i]);
		}
	}

	WSACleanup();
	return true;
}


std::string CDNS::getHostAt(const size_t index) {
	if (index < hostIps_.size()) {
		std::string s = hostIps_.at(index); ;
		return hostIps_.at(index); 
	} else {
		return _T("");
	}
}


size_t CDNS::getNumberOfHosts() const { 
	return hostIps_.size(); 
}

size_t CDNS::getNumberOfIP() const {
	return dnsIps_.size(); 
}


std::string CDNS::getIPAt(const size_t index) {
	if (index < dnsIps_.size())
		return dnsIps_.at(index);
	else
		return _T("");
}