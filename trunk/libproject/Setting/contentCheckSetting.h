// file : ImageCheckSetting.h

#ifndef _SETTING_CONTENTCHECKSETTING_H__
#define _SETTING_CONTENTCHECKSETTING_H__

#include <webcontenttype.h>

// class ImageCheckSetting
// ���ฺ���ͼƬ�Ŀ���
// ���Դ���ֻ������Ƽ�⣬��������ʵ�ʵļ�⣬��ΪͼƬ���ܴܺ�
// �����Խ���̱߽���м�⣬���ܶ�ϵͳ����Ӱ��ϴ�

// ע����������ʹ����ÿһλ����һ�����ͣ�������ǿ���ʹ��΢�������й���
class ContentCheckSetting {
public:
	ContentCheckSetting(void);
	~ContentCheckSetting(void);
public:
	void enableCheck(const bool checked, const unsigned type);

	// �˺����������վ��ͼƬ���ͽ����ж�
	// �����վ�ڰ�����֮�ڣ��Ͳ�������
	bool needCheck(const unsigned type) const;
private:
	unsigned content_type_;
};

#endif  // _SETTING_CONTENTCHECKSETTING_H__
