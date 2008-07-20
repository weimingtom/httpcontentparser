#ifndef _SETTING_IMAGE_CHECK_H__
#define _SETTING_IMAGE_CHECK_H__

#include <set>
#include <string>

class DNSList;

// ImageCheckֻ���"���ͼƬ�Ĺ��� ��ͼƬ���ݹ���ļ��
// ����ֱ�ӷŵ�SPI���н��С�
// �������Ա������ݵĴ���
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

	// ֻ�е�ͼƬλ��������ֵ֮���ʱ��
	// ���ǲŶ�ͼƬ����CHECK
	int max_size_, min_size_;

	const DNSList *dns_list_;
	ImageCheck(void);
};

#endif  // _SETTING_IMAGE_CHECK_H__