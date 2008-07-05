#ifndef _RULES_DEFINES_H__
#define _RULES_DEFINES_H__

#include <set>

// 规则数据
typedef struct _ipport {
	unsigned int ip;
	unsigned int port;  // 只需要8位，不过存储起来是一样的。所以...
} IPRULE;

typedef std::set<IPRULE> IPRULES_SET;

// 存储规则的接口
class RulesStorer {
public:
	virtual addIpAddress(unsigned int ip) = 0;
	virtual adddns(const std::string &dns) = 0;
	virtual addIpAndPort(unsigned int ip, unsigned int port) = 0;
};

#define ALL_PORT 0

#endif  // _RULES_DEFINES_H__