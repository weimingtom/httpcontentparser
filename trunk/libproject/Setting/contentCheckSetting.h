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

	// �˺����������վ��ͼƬ���ͽ����ж�
	// �����վ�ڰ�����֮�ڣ��Ͳ�������
	bool needCheck(const unsigned type) const;

	// �ɽ��̶ȣ���0��4���ֵ��Ĭ��Ϊ2
	int getTightness() const { return tightness_;}
	void setTightness(const int new_tight) { tightness_ = new_tight;}
	bool isSettingNeedCheck(const unsigned type) const;
private:
	unsigned content_type_;
	int	tightness_;

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
