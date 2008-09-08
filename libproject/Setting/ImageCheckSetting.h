// file : ImageCheckSetting.h

#ifndef _SETTING_IMAGECHECKSETTING_H__
#define _SETTING_IMAGECHECKSETTING_H__

#include <imagetypes.h>

// class ImageCheckSetting
// 本类负责对图片的控制
// 足以此类只负责控制检测，而不进行实际的检测，因为图片可能很大
// 如果跨越进程边界进行检测，可能对系统性能影响较大
class ImageCheckSetting {
public:
	ImageCheckSetting(void);
	~ImageCheckSetting(void);
public:
	void enableImageCheck(const bool checked, const int type);

	// 此函数会根据网站及图片类型进行判断
	// 如果网站在白名单之内，就不会检测了
	bool needCheck() const;
private:
};

#endif  // _SETTING_IMAGECHECKSETTING_H__
