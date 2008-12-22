// file : ImageCheckSetting.h

#ifndef _SETTING_CONTENTCHECKSETTING_H__
#define _SETTING_CONTENTCHECKSETTING_H__

#include <webcontenttype.h>
#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>

// class ImageCheckSetting
// 本类负责对图片的控制
// 足以此类只负责控制检测，而不进行实际的检测，因为图片可能很大
// 如果跨越进程边界进行检测，可能对系统性能影响较大

// 注意由于我们使用了每一位代表一个类型，因此我们可以使用微操作进行过滤
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
	// 此函数会根据网站及图片类型进行判断
	// 如果网站在白名单之内，就不会检测了
	bool needCheck(const unsigned type) const;
	bool needCheckBySize(const int size) const;
	bool enabledCheckBySize() const;
	void enableCheckBySize(const bool enabled);

	void getCheckedScope(long * scope_min, long * scope_max);
	// 松紧程度，有0～4五个值，默认为2
	int getImageCheckTightness() const { return image_tightness_;}
	void setImageCheckTightness(const int new_tight) { image_tightness_ = new_tight;}
	bool isSettingNeedCheck(const unsigned type) const;
private:
	unsigned content_type_;
	int	image_tightness_;

	// 检测大小
	bool enabled_check_by_size_;
	int	min_check_size_, max_check_size_;
	void defaultSetting();
// XML file
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement * saveConfig(TiXmlElement * root);
private:
	// 处理各个规则的具体细节
	int getImageRule(TiXmlElement * ele);
	int setImageCheck(const TCHAR *imagetype, const TCHAR *enable);
	TiXmlElement * saveImageRule(TiXmlElement *rules_root);
};

#endif  // _SETTING_CONTENTCHECKSETTING_H__
