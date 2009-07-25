#ifndef _UTILITY_SEACHPACKET_H__
#define _UTILITY_SEACHPACKET_H__

#include <utility\httprequestpacket.h>

class SeachPacket {
public:
	SeachPacket(void);
	~SeachPacket(void);

public:
	// ����ֵ 0
	// ��ʾû�н��
	// ��0��ʾ�����ɹ�
	INT_PTR parse(const char * oper, const char * host_name);

	// ��ȡ��Ϣ
	INT_PTR get_seach_word(char *buf, const INT_PTR size);

	enum {
		SEACH_ENGINE_UNKNOWN = 0,
		SEACH_ENGINE_GOOGLE = 1,
		SEACH_ENGINE_YAHOO,
		SEACH_ENGINE_BAIDU
	};
	
	INT_PTR getSeachEngineType() const { return seach_engine_;}
private:
	INT_PTR parse_google(const char * oper);
	INT_PTR parse_baidu(const char * oper);
	INT_PTR parse_yahoo(const char * oper);

	bool is_yahoo_seach(const char *oper);
	bool is_baidu_seach(const char *oper);
	bool is_google_seach(const char *oper);
private:
	char seach_word[MAX_PATH];
	char language_[MAX_PATH];
	
	INT_PTR seach_engine_;
};

#endif  // _UTILITY_SEACHPACKET_H__