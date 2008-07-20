#ifndef _SETTING_IMAGE_CHECK_H__
#define _SETTING_IMAGE_CHECK_H__

#include <set>
#include <string>

class DNSList;

// ImageCheck只检测"检测图片的规则， 对图片内容规则的检测
// 我们直接放到SPI当中进行“
// 这样可以避免数据的传输
class ImageCheck {
public:
	ImageCheck(const DNSList *dns_list);
	~ImageCheck(void);

public:
	void enableImageCheck(const bool checked);
	void checkPNG(const bool checked);
	void checkJPEG(const bool checked);
	void checkBMP(const bool checked);
	void enableShowImage(const bool showed);

	int checkImage(const std::string &dns);

private:
	bool show_image_;
	bool check_png_;
	bool check_jpeg_;
	bool check_bmp_;

	// 只有当图片位于这两个值之间的时候，
	// 我们才对图片进行CHECK
	int max_size_, min_size_;

	const DNSList *dns_list_;
	ImageCheck(void);
};

#endif  // _SETTING_IMAGE_CHECK_H__