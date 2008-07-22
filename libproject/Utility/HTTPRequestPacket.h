#ifndef _UTILITY_HTTP_REQUEST_PACKET_H__
#define _UTILITY_HTTP_REQUEST_PACKET_H__


class HTTP_REQUEST_HEADER {
public:
	HTTP_REQUEST_HEADER();
	~HTTP_REQUEST_HEADER();

	int parse(const char * line);
private:

};

class HTTPRequestPacket {
public:
	HTTPRequestPacket(void);
	~HTTPRequestPacket(void);
public:
	int addPacket(const char * buf, const int len);
	
};

#endif  // _UTILITY_HTTP_REQUEST_PACKET_H__