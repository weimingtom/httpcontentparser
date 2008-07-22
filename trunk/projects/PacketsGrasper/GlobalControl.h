#ifndef _PACKET_GRASPHER_GLOBALCONTROL_H__
#define _PACKET_GRASPHER_GLOBALCONTROL_H__

#include <string>

// 控制整体的规则
// 所有的内容都通过它进行检查

// 主要规则(每个规则包括三项， 检查，不检查， 不显示)
// 1. 验证DNS
// 2. 验证图片
// 3. 验证HTML
// 4. 验证FLASH

class HTTP_RESPONSE_HEADER;
class HTTPPacket;

class GlobalControl {
public:
	static GlobalControl * getInstance();

	// 内容是否需要检查
	bool checkHTTPHeader(HTTP_RESPONSE_HEADER *header);

	// 检查HTTP包的内容（注：HTTP包应该是完整的）
	bool checkHTTPContent(HTTPPacket *packet);

	// 检查IP地址及端口号(注：如果端口号为0，则只检查IP地址)
	bool checkDNS(const std::string &dns_name);
	~GlobalControl(void);
private:
	void Update();
	bool update_;

	GlobalControl(void);
	static GlobalControl * pInstance_;
};

#endif  // _PACKET_GRASPHER_GLOBALCONTROL_H__