#ifndef _SELECT_IO_WEBSITERECORDER_H__
#define _SELECT_IO_WEBSITERECORDER_H__

#include <map>
#include <string>

#define PORN_SCORE 50

// class WebsiteRecorder
// �������ڼ�¼website
// ����ֱ�ӱ������� ��˲���Ҫ���ǰ������� ��Ϊ���������ֽ���
// ���ͼƬ���ݵĴ�����д���
class WebsiteRecorder {
public:
	WebsiteRecorder(void);
	~WebsiteRecorder(void);

public:
	void initialize();
	void saveWebsites();

	// ��������һ��website
	void updateWebsites(const std::string &main_dns, const int score);
private:
	void getServiceSetting();

	bool savePornURLs() const { return save_porn_url_; }
	bool saveURLs() const { return save_url_; }
private:
	typedef std::map<std::string, int> ADDRESS_SCORE;
	ADDRESS_SCORE address_score_;

	// ��װĿ¼
	TCHAR porn_path[MAX_PATH];
	TCHAR normal_path[MAX_PATH];

	// �Ƿ���Ҫ����
	bool save_porn_url_;
	bool save_url_;

	// �Ƿ��Ѿ���ʼ����
	bool initialized_;
};

#endif  // _SELECT_IO_WEBSITERECORDER_H__