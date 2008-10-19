// file : ImageCheckSetting.h

#ifndef _SETTING_CONTENTCHECKSETTING_H__
#define _SETTING_CONTENTCHECKSETTING_H__

#include <webcontenttype.h>
#include <settingitem.h>

// class ImageCheckSetting
// ���ฺ���ͼƬ�Ŀ���
// ���Դ���ֻ������Ƽ�⣬��������ʵ�ʵļ�⣬��ΪͼƬ���ܴܺ�
// �����Խ���̱߽���м�⣬���ܶ�ϵͳ����Ӱ��ϴ�

// ע����������ʹ����ÿһλ����һ�����ͣ�������ǿ���ʹ��΢�������й���
class ContentCheckSetting : public SettingItem {
public:
	ContentCheckSetting(void);
	~ContentCheckSetting(void);
public:
	void enableCheck(const unsigned type, const bool checked);

	// �˺����������վ��ͼƬ���ͽ����ж�
	// �����վ�ڰ�����֮�ڣ��Ͳ�������
	bool needCheck(const unsigned type) const;

	// �ɽ��̶ȣ���0��4���ֵ��Ĭ��Ϊ2
	int getTightness() const { return tightness_;}
	void setTightness(const int new_tight) { tightness_ = new_tight;}
private:
	unsigned content_type_;
	int	tightness_;

	void defaultSetting();
};

#endif  // _SETTING_CONTENTCHECKSETTING_H__
