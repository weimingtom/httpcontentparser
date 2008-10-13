#ifndef _UTILITY_SEACHPACKET_H__
#define _UTILITY_SEACHPACKET_H__

#include <utility\httprequestpacket.h>

class SeachPacket {
public:
	SeachPacket(void);
	~SeachPacket(void);

public:
	int parse(const char * oper, const char * host_name);

	// 获取信息
	int get_seach_word(char *buf, const int size);

	enum {
		SEACH_ENGINE_UNKNOWN = 0,
		SEACH_ENGINE_GOOGLE = 1,
		SEACH_ENGINE_YAHOO,
		SEACH_ENGINE_BAIDU
	};

	int getSeachEngineType() const { return seach_engine_;}
private:
	int parse_google(const char * oper);
	int parse_baidu(const char * oper);
	int parse_yahoo(const char * oper);

	bool is_yahoo_seach(const char *oper);
	bool is_baidu_seach(const char *oper);
	bool is_google_seach(const char *oper);
private:
	char seach_word[MAX_PATH];
	char language_[MAX_PATH];
	
	int seach_engine_;
};

#endif  // _UTILITY_SEACHPACKET_H__