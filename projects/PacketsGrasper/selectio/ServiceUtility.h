#ifndef _SERVICE_UTILITY_SERVICEUTILITY_H__
#define _SERVICE_UTILITY_SERVICEUTILITY_H__

#include <winsock2.h>
#include <string>
#include <vector>
#include <utility\HttpPacket.h>

class HTTPRequestPacket;

bool accessNetword();
bool checkHTTPRequest(HTTPRequestPacket * packet);
bool checkSeachRule(HTTPRequestPacket * packet);
bool checkDNS(const char * dns_name);
void repairApplication();



#endif  // _SERVICE_UTILITY_SERVICEUTILITY_H__