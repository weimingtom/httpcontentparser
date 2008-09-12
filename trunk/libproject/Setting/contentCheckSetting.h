// file : ImageCheckSetting.h

#ifndef _SETTING_CONTENTCHECKSETTING_H__
#define _SETTING_CONTENTCHECKSETTING_H__

#include <webcontenttype.h>

// class ImageCheckSetting
// 本类负责对图片的控制
// 足以此类只负责控制检测，而不进行实际的检测，因为图片可能很大
// 如果跨越进程边界进行检测，可能对系统性能影响较大

// 注意由于我们使用了每一位代表一个类型，因此我们可以使用微操作进行过滤
class ContentCheckSetting {
public:
	ContentCheckSetting(void);
	~ContentCheckSetting(void);
public:
	void enableCheck(const bool checked, const unsigned type);

	// 此函数会根据网站及图片类型进行判断
	// 如果网站在白名单之内，就不会检测了
	bool needCheck(const unsigned type) const;
private:
	unsigned content_type_;
};

#endif  // _SETTING_CONTENTCHECKSETTING_H__
