#ifndef _SELECT_IO_WEBSITERECORDER_H__
#define _SELECT_IO_WEBSITERECORDER_H__

#include <map>
#include <string>

#define PORN_SCORE 50

// ����౻�����ˣ�ʹ��COM Service��¼���ʵ���վ
// 1. �û�����ÿһ����վ��Ҫ����COM Service
// 2. ������SPIͬʱ����ͬһ���ļ�

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
	void addDNS(const std::string &main_dns, const std::string &full);
private:
	void getServiceSetting();

	bool savePornURLs() const { return save_porn_url_; }
	bool saveURLs() const { return save_url_; }

	void saveDNSItem(const std::string &main_dns, std::fstream &s);
private:
	typedef std::map<std::string, int> ADDRESS_SCORE;
	ADDRESS_SCORE address_score_;

	// ÿһ��DNS��Ӧ����ַ
	typedef std::multimap<std::string, std::string> FULL_DNS_MAP;
	FULL_DNS_MAP fullDNS;


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