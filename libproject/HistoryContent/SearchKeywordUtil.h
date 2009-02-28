#ifndef _HISTORY_CONTENT_SEACHKEYWORDUTIL_H__
#define _HISTORY_CONTENT_SEACHKEYWORDUTIL_H__

#include <string>
#include <map>
#include <windows.h>
#include <searchengine_define.h>
#include <utility\timeutility.h>
#include <fstream>

// class SeachKeywordUtil
// 此类主要提供了保存及读取Seachword相关信息的工具函数
class SeachKeywordUtil {
public:
	SeachKeywordUtil(void);
	~SeachKeywordUtil(void);

public:
	int addKeyword(const std::string &keyword, const int seach_engine);
	
	// 保存信息
	int save();
	
	// 从文件中读取信息
	int load();

private:
	int insertItem(const std::string &keyword, const std::string & search_engine, const std::string & last_time , const std::string &times );
	int parseString(const std::string &line);

private:
	typedef struct _tagKeywordInfo {
		int engine_type;			// 使用的搜索引擎
		int seach_count;			// 搜错的次数
		FILETIME   last_seach;	// 最后一次搜索的时间
	}KEYWORD_DATA;

	typedef std::map<std::string, KEYWORD_DATA>  SEARCH_WORD_DATA;

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
			recordfile_.write(SeachKeywordUtil::SEPERATOR, SeachKeywordUtil::SEPERATOR_LEN);
			
			// 记录搜索引擎的类型
			_snprintf(buffer, BUF_SIZE, "%d%s", iter.second.engine_type, SeachKeywordUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));
			
			// 记录上一次搜索的时间
			_snprintf(buffer, BUF_SIZE, "%llu%s", iter.second.last_seach, SeachKeywordUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));

			// 记录搜错次数
			_snprintf(buffer, BUF_SIZE, "%d%s", iter.second.seach_count, SeachKeywordUtil::NEW_LINE);
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

#endif // _HISTORY_CONTENT_SEACHKEYWORDUTIL_H__