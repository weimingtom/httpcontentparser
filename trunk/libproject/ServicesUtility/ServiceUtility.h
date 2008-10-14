#ifndef _SERVICE_UTILITY_SERVICEUTILITY_H__
#define _SERVICE_UTILITY_SERVICEUTILITY_H__

#include <winsock2.h>
#include <string>
#include <utility\HttpPacket.h>

class HTTPRequestPacket;

bool accessNetword();
bool checkHTTPRequest(WSABUF *buf, const int count);
bool checkSeachRule(HTTPRequestPacket & packet);
bool checkDNS(const char * dns_name);

#endif  // _SERVICE_UTILITY_SERVICEUTILITY_H__