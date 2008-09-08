// file : ImageCheckSetting.h

#ifndef _SETTING_IMAGECHECKSETTING_H__
#define _SETTING_IMAGECHECKSETTING_H__

#include <imagetypes.h>

// class ImageCheckSetting
// ���ฺ���ͼƬ�Ŀ���
// ���Դ���ֻ������Ƽ�⣬��������ʵ�ʵļ�⣬��ΪͼƬ���ܴܺ�
// �����Խ���̱߽���м�⣬���ܶ�ϵͳ����Ӱ��ϴ�
class ImageCheckSetting {
public:
	ImageCheckSetting(void);
	~ImageCheckSetting(void);
public:
	void enableImageCheck(const bool checked, const int type);

	// �˺����������վ��ͼƬ���ͽ����ж�
	// �����վ�ڰ�����֮�ڣ��Ͳ�������
	bool needCheck() const;
private:
};

#endif  // _SETTING_IMAGECHECKSETTING_H__
