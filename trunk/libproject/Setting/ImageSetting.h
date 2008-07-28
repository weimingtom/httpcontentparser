#ifndef _SETTING_IMAGE_CHECK_H__
#define _SETTING_IMAGE_CHECK_H__

#include <set>
#include <string>

class DNSList;

// ImageSettingֻ���"���ͼƬ�Ĺ��� ��ͼƬ���ݹ���ļ��
// ����ֱ�ӷŵ�SPI���н��С�
// �������Ա������ݵĴ���
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

	// ֻ�е�ͼƬλ��������ֵ֮���ʱ��
	// ���ǲŶ�ͼƬ����CHECK
	int max_size_, min_size_;

	const DNSList *dns_list_;
	ImageSetting(void);
};

#endif  // _SETTING_IMAGE_CHECK_H__