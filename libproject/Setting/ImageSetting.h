#ifndef _SETTING_IMAGE_CHECK_H__
#define _SETTING_IMAGE_CHECK_H__

#include <set>
#include <string>

class DNSList;

// ImageSetting只检测"检测图片的规则， 对图片内容规则的检测
// 我们直接放到SPI当中进行“
// 这样可以避免数据的传输
class ImageSetting {
public:
	ImageSetting(const DNSList *dns_list);
	~ImageSetting(void);

public:
	void enableShowImage(const bool showed);
	void enableCheck(const int type, const bool enable);
	bool needCheck(const int type) const;
	bool showImage() const;
private:
	bool show_image_;
	bool check_png_;
	bool check_jpeg_;
	bool check_bmp_;
	bool check_gif_;

	// 只有当图片位于这两个值之间的时候，
	// 我们才对图片进行CHECK
	int max_size_, min_size_;

	const DNSList *dns_list_;
	ImageSetting(void);
};

#endif  // _SETTING_IMAGE_CHECK_H__