#ifndef _HISTORY_CONTENT_WEBSITESUTIL_H__
#define _HISTORY_CONTENT_WEBSITESUTIL_H__

#include <windows.h>
#include<string>
#include <map>
#include <fstream>

class WebsitesUtil {
public:
	WebsitesUtil(void);
	~WebsitesUtil(void);
public:
	// 数据的定义
	typedef struct _tagWebsiteInfo {
		int visit_count;			// 网站的访问的次数
		FILETIME   latest_visit;	// 最后一次访问的时间
	}WEBSITE_DATA;
public:
	int addWebsite(const std::string &websites);

	// 保存信息
	int save(const std::string &filename);

	// 从文件中读取信息
	int load(const std::string &filename);

	void clear();

	// 枚举对象的方法
	// 这种方法好吗? 至少可以枚举对象吧！
	class DataEnumerator {
	public:
		virtual int DealItemData(const std::string &name, const WEBSITE_DATA &item) = 0;
	};
	int enumerate(DataEnumerator * const enumerator);

	// 获取
	int getSize() const ;
	int getFirst(std::string *name, WEBSITE_DATA * data) const;
	int getNext(const std::string &cur, std::string * name, WEBSITE_DATA * data) const;

private:
	int insertItem(const std::string &websites, const std::string & last_time , const std::string &times );
	int parseString(const std::string &line);
private:
	typedef std::map<std::string, WEBSITE_DATA>  SEARCH_WORD_DATA;

	SEARCH_WORD_DATA data_;

	// 用于记录历史到文件当中
	friend class DataRecorder;
	class DataRecorder {
	public:
		DataRecorder(std::fstream &f) : recordfile_(f)  {}

	public:
		void operator() (const SEARCH_WORD_DATA::value_type  &  iter) {
			const int BUF_SIZE = 512;
			TCHAR buffer[BUF_SIZE];
			recordfile_.write(iter.first.c_str(),  (std::streamsize)iter.first.length());
			recordfile_.write(WebsitesUtil::SEPERATOR, WebsitesUtil::SEPERATOR_LEN);

			// 记录上一次搜索的时间
			_snprintf(buffer, BUF_SIZE, "%u-%u%s", iter.second.latest_visit.dwHighDateTime, iter.second.latest_visit.dwLowDateTime, WebsitesUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));

			// 记录搜错次数
			_snprintf(buffer, BUF_SIZE, "%d%s", iter.second.visit_count, WebsitesUtil::NEW_LINE);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));
		}

	private:
		std::fstream &recordfile_;
	};

private:
	const static char * SEPERATOR;
	const static int SEPERATOR_LEN = 1;
	const static char * NEW_LINE;
	const static int NEW_LINE_LEN = 1;
};

#endif  // _HISTORY_CONTENT_WEBSITESUTIL_H__