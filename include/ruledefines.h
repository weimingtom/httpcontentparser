#ifndef _RULES_DEFINES_H__
#define _RULES_DEFINES_H__

#include <set>

// ��������
typedef struct _ipport {
	unsigned int ip;
	unsigned int port;  // ֻ��Ҫ8λ�������洢������һ���ġ�����...
} IPRULE;

typedef std::set<IPRULE> IPRULES_SET;

// �洢����Ľӿ�
class RulesStorer {
public:
	virtual addIpAddress(unsigned int ip) = 0;
	virtual adddns(const std::string &dns) = 0;
	virtual addIpAndPort(unsigned int ip, unsigned int port) = 0;
};

#define ALL_PORT 0

#endif  // _RULES_DEFINES_H__