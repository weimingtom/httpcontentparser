// file : ImageCheckSetting.h

#ifndef _SETTING_CONTENTCHECKSETTING_H__
#define _SETTING_CONTENTCHECKSETTING_H__

#include <webcontenttype.h>
#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>

// class ImageCheckSetting
// ���ฺ���ͼƬ�Ŀ���
// ���Դ���ֻ������Ƽ�⣬��������ʵ�ʵļ�⣬��ΪͼƬ���ܴܺ�
// �����Խ���̱߽���м�⣬���ܶ�ϵͳ����Ӱ��ϴ�

// ע����������ʹ����ÿһλ����һ�����ͣ�������ǿ���ʹ��΢�������й���
class ContentCheckSetting : public SettingItem, public ConfigItem {
public:
	ContentCheckSetting(void);
	~ContentCheckSetting(void);
public:
	void enableCheck(const unsigned type, const bool checked);
	void setCheckScope(const int min_size, const int max_size) {
		min_check_size_ = min_size;
		max_check_size_ = max_size;
	}
	// �˺����������վ��ͼƬ���ͽ����ж�
	// �����վ�ڰ�����֮�ڣ��Ͳ�������
	bool needCheck(const unsigned type) const;
	bool needCheckBySize(const int size) const;
	bool enabledCheckBySize() const;
	void enableCheckBySize(const bool enabled);

	void getCheckedScope(long * scope_min, long * scope_max);
	// �ɽ��̶ȣ���0��4���ֵ��Ĭ��Ϊ2
	int getImageCheckTightness() const { return image_tightness_;}
	void setImageCheckTightness(const int new_tight) { image_tightness_ = new_tight;}
	bool isSettingNeedCheck(const unsigned type) const;
private:
	unsigned content_type_;
	int	image_tightness_;

	// ����С
	bool enabled_check_by_size_;
	int	min_check_size_, max_check_size_;
	void defaultSetting();
// XML file
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	// �����������ľ���ϸ��
	int getImageRule(TiXmlElement * ele);
	int setImageCheck(const TCHAR *imagetype, const TCHAR *enable);
	TiXmlElement * saveImageRule(TiXmlElement *rules_root);
};

#endif  // _SETTING_CONTENTCHECKSETTING_H__
