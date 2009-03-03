#ifndef _HISTORY_CONTENT_SEACHKEYWORDUTIL_H__
#define _HISTORY_CONTENT_SEACHKEYWORDUTIL_H__

#include <string>
#include <map>
#include <windows.h>
#include <searchengine_define.h>
#include <utility\timeutility.h>
#include <fstream>

// class SeachKeywordUtil
// ������Ҫ�ṩ�˱��漰��ȡSeachword�����Ϣ�Ĺ��ߺ���
class SeachKeywordUtil {
public:
	SeachKeywordUtil(void);
	~SeachKeywordUtil(void);

public:
	// ���ݵĶ���
	typedef struct _tagKeywordInfo {
		int engine_type;			// ʹ�õ���������
		int seach_count;			// �Ѵ�Ĵ���
		FILETIME   last_seach;	// ���һ��������ʱ��
	}KEYWORD_DATA;

public:
	int addKeyword(const std::string &keyword, const int seach_engine);

	// ������Ϣ
	int save(const std::string &filename);
	
	// ���ļ��ж�ȡ��Ϣ
	int load(const std::string &filename);

	// ö�ٶ���ķ���
	// ���ַ�������? ���ٿ���ö�ٶ���ɣ�
	class DataEnumerator {
	public:
		virtual int DealItemData(const std::string &name, const KEYWORD_DATA &item) = 0;
	};
	int enumerate(DataEnumerator * const enumerator);

	// ��ȡ
	int getSize() const ;
	int getFirst(std::string *name, KEYWORD_DATA * data) const;
	int getNext(const std::string &cur, std::string * name, KEYWORD_DATA * data) const;

private:
	int insertItem(const std::string &keyword, const std::string & search_engine, const std::string & last_time , const std::string &times );
	int parseString(const std::string &line);
private:
	typedef std::map<std::string, KEYWORD_DATA>  SEARCH_WORD_DATA;

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
			recordfile_.write(SeachKeywordUtil::SEPERATOR, SeachKeywordUtil::SEPERATOR_LEN);
			
			// ��¼�������������
			_snprintf(buffer, BUF_SIZE, "%d%s", iter.second.engine_type, SeachKeywordUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));
			
			// ��¼��һ��������ʱ��
			_snprintf(buffer, BUF_SIZE, "%u-%u%s", iter.second.last_seach.dwHighDateTime, iter.second.last_seach.dwLowDateTime, SeachKeywordUtil::SEPERATOR);
			recordfile_.write(buffer, static_cast<std::streamsize>(_tcslen(buffer)));

			// ��¼�Ѵ����
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