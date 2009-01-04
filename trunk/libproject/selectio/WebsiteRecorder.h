#ifndef _SELECT_IO_WEBSITERECORDER_H__
#define _SELECT_IO_WEBSITERECORDER_H__

#include <map>
#include <string>

#define PORN_SCORE 50

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
private:
	void getServiceSetting();

	bool savePornURLs() const { return save_porn_url_; }
	bool saveURLs() const { return save_url_; }
private:
	typedef std::map<std::string, int> ADDRESS_SCORE;
	ADDRESS_SCORE address_score_;

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