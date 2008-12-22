#ifndef _PACKET_GRASPHER_GLOBALCONTROL_H__
#define _PACKET_GRASPHER_GLOBALCONTROL_H__

#include <string>

// ��������Ĺ���
// ���е����ݶ�ͨ�������м��

// ��Ҫ����(ÿ������������ ��飬����飬 ����ʾ)
// 1. ��֤DNS
// 2. ��֤ͼƬ
// 3. ��֤HTML
// 4. ��֤FLASH

class HTTP_RESPONSE_HEADER;
class HTTPPacket;

class GlobalControl {
public:
	static GlobalControl * getInstance();

	// �����Ƿ���Ҫ���
	bool checkHTTPHeader(HTTP_RESPONSE_HEADER *header);

	// ���HTTP�������ݣ�ע��HTTP��Ӧ���������ģ�
	bool checkHTTPContent(HTTPPacket *packet);

	// ���IP��ַ���˿ں�(ע������˿ں�Ϊ0����ֻ���IP��ַ)
	bool checkDNS(const std::string &dns_name);
	~GlobalControl(void);
private:
	void Update();
	bool update_;

	GlobalControl(void);
	static GlobalControl * pInstance_;
};

#endif  // _PACKET_GRASPHER_GLOBALCONTROL_H__