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
	// ���ݵĶ���
	typedef struct _tagWebsiteInfo {
		int visit_count;			// ��վ�ķ��ʵĴ���
		FILETIME   latest_visit;	// ���һ�η��ʵ�ʱ��
	}WEBSITE_DATA;
public:
	int addWebsite(const std::string &websites);

	// ������Ϣ
	int save(const std::string &filename);

	// ���ļ��ж�ȡ��Ϣ
	int load(const std::string &filename);

	void clear();

	// ö�ٶ���ķ���
	// ���ַ�������? ���ٿ���ö�ٶ���ɣ�
	class DataEnumerator {
	public:
		virtual int DealItemData(const std::string &name, const WEBSITE_DATA &item) = 0;
	};
	int enumerate(DataEnumerator * const enumerator);

	// ��ȡ
	int getSize() const ;
	int getFirst(std::string *name, WEBSITE_DATA * data) const;
	int getNext(const std::string &cur, std::string * name, WEBSITE_DATA * data) const;

private:
	int insertItem(const std::string &websites, const std::string & last_time , const std::string &times );
	int parseString(const std::string &line);
private:
	typedef std::map<std::string, WEBSITE_DATA>  SEARCH_WORD_DATA;

	SEARCH_WORD_DATA data_;

	// ���ڼ�¼��ʷ���ļ�����
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

			// ��¼��һ��������ʱ��
			_snprintf(buffer, BUF_SIZE, "%u-%u%s", iter.second.latest_visit.dwHighDateTime, iter.second.latest_visit.dwLowDateTime, WebsitesUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));

			// ��¼�Ѵ����
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