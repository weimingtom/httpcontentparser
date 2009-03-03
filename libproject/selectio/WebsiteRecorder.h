#ifndef _SELECT_IO_WEBSITERECORDER_H__
#define _SELECT_IO_WEBSITERECORDER_H__

#include <map>
#include <string>

#define PORN_SCORE 50

// 这个类被废弃了，使用COM Service记录访问的网站
// 1. 用户访问每一个网站都要调用COM Service
// 2. 避免多个SPI同时访问同一个文件

// class WebsiteRecorder
// 此类用于记录website
// 此类直接保存结果， 因此不需要考虑白名单， 因为白名单部分将有
// 检测图片内容的代码进行处理
class WebsiteRecorder {
public:
	WebsiteRecorder(void);
	~WebsiteRecorder(void);

public:
	void initialize();
	void saveWebsites();

	// 新增增加一个website
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

	// 每一个DNS对应的网址
	typedef std::multimap<std::string, std::string> FULL_DNS_MAP;
	FULL_DNS_MAP fullDNS;


	// 安装目录
	TCHAR porn_path[MAX_PATH];
	TCHAR normal_path[MAX_PATH];

	// 是否需要保存
	bool save_porn_url_;
	bool save_url_;

	// 是否已经初始化了
	bool initialized_;
};

#endif  // _SELECT_IO_WEBSITERECORDER_H__