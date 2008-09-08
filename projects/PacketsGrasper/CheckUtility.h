#ifndef _PACKETS_GRASPER_CHECKURL_H__
#define _PACKETS_GRASPER_CHECKURL_H__

#include <string>
#include <utility\HttpPacket.h>

bool checkDNS(const char* DNS_NAME);
bool checkHTTPRequest(WSABUF *buf, const int count);

void saveWebLink();
void saveImage();

#endif  // _PACKETS_GRASPER_CHECKURL_H__