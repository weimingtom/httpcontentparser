#ifndef _SELECT_IO_CONTENT_FILTER_H__
#define _SELECT_IO_CONTENT_FILTER_H__

class HTTPPacket;

class ContentFilter {
public:
	ContentFilter(void);
	~ContentFilter(void);

	bool needCheck(const int type);
	bool checkHTTPContent(HTTPPacket *packet);
private:
	bool isImage(const int type) const;
	bool checkImage(const int type, char * buf, const int len); 
	bool checkText(const int type, char * buf, const int len);
};

#endif  // _SELECT_IO_CONTENT_FILTER_H__