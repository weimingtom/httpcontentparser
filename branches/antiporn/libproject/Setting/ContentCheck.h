#ifndef _SETTING_CONTENT_CHECK_H__
#define _SETTING_CONTENT_CHECK_H__

class HTTPPacket;
class DNSSetting;

// ���й������ݵ�checker��Ҫͨ�������д���
// class ContentCheck�����HTTPPacket�������Զ�����һ��checker
// �����ݽ���check

// ÿһ��checkerӦ���ܹ��õ�ȫ�ֵ����ã�������ȫ�ֵ����ý��м��
class ContentCheck {
public:
	static ContentCheck * getContentChecker(const HTTPPacket *packet, DNSSetting *globalSetting);
	~ContentCheck(void);

	// ��������
	virtual bool check(HTTPPacket *packet) = 0;
protected:
	ContentCheck();
	DNSSetting *globalSetting_;
};

#endif  // _SETTING_CONTENT_CHECK_H__
