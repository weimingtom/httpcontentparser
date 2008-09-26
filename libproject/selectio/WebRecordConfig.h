#ifndef _SELECTIO_WEBRECORDCONFIG_H__
#define _SELECTIO_WEBRECORDCONFIG_H__

#include <webcontenttype.h>
#include <string>
#include <set>
#include <map>

#define REPOS_ROOT_NAME		TEXT("history")
#define REPOS_TYPE_PORN		TEXT("porn")
#define REPOS_TYPE_NORMAL	TEXT("normal")
#define REPOS_TYPE_UNKNOWN	TEXT("unknown")


#define REPOS_NORMAL_IMAGE_ROOT			TEXT("normal_images")
#define REPOS_NORMAL_TEXT_ROOT			TEXT("normal_texts")

#define REPOS_UNKNOWN_IMAGE_ROOT		TEXT("unknown_images")
#define REPOS_UNKNOWN_TEXT_ROOT			TEXT("unknown_texts")

#define REPOS_PORN_IMAGE_ROOT			TEXT("porn_images")
#define REPOS_PORN_TEXT_ROOT			TEXT("porn_texts")

#define REPOS_IMAGE_ITEM			TEXT("image")
#define REPOS_TEXT_ITEM				TEXT("text")
#define REPOS_ITEM_ATTR_PATH		TEXT("path")
#define REPOS_ITEM_ATTR_TIME		TEXT("time")

class TiXmlElement;
class TiXmlNode;

// class WebRecordConfig
// 此类负责操作保存历史的配置文件
class WebRecordConfig {
public:
	WebRecordConfig(const TCHAR *filename);
	~WebRecordConfig(void);
public:
	int addItem(const TCHAR * filename, const int check_result, const int content_type);
private:
	typedef struct _tagRecordItem {
		std::string time;
		std::string path;

		// 不学要实现 ;)
		friend bool operator < (const struct _tagRecordItem &item1,
					const struct _tagRecordItem &item2) {
			return true;
		}
	}RecordItem;

	typedef std::set<RecordItem> BUFFER_RECORD_SET;

	BUFFER_RECORD_SET image_normal_set_;
	BUFFER_RECORD_SET image_porn_set_;
	BUFFER_RECORD_SET image_unknown_set_;

	BUFFER_RECORD_SET text_porn_set_;
	BUFFER_RECORD_SET text_normal_set_;
	BUFFER_RECORD_SET text_unknown_set_;

	// 主要用于寻找错误，如果传递参数错误，信息将保存于此
	BUFFER_RECORD_SET unknown_at_all_;
private:
	void addToBufferSet(const RecordItem &item, const int check_result, const int content_type);

	BUFFER_RECORD_SET* getCorrectBufferSet(const int check_result, const int content_type);
	// 写入缓冲区
	void flush();
	void bufferedFlush();

	int but_cnt_;
	static const int max_buf_count_ = 40;

	// 写入
	void writePornText(TiXmlElement * text_root);
	void writeNormalText(TiXmlElement * text_root);
	void writeUnknownText(TiXmlElement * text_root);

	void writePornImage(TiXmlElement * image_root);
	void writeNormalImage(TiXmlElement * image_root);
	void writeUnknownImage(TiXmlElement * image_root);
	void writeItems(BUFFER_RECORD_SET *itemsets, const int content_type, TiXmlElement * image_root);

	// 获取节点
	TiXmlElement * getNormalImageRoot(TiXmlElement * root);
	TiXmlElement * getPornImageRoot(TiXmlElement * root);
	TiXmlElement * getUnknownImageRoot(TiXmlElement * root);
	TiXmlElement * getNormalTextRoot(TiXmlElement * root);
	TiXmlElement * getPornTextRoot(TiXmlElement * root);
	TiXmlElement * getUnknownTextRoot(TiXmlElement * root);

protected:
	WebRecordConfig(void);
	// 检测XML文件是否合法
	TCHAR filename_[MAX_PATH];
};


#endif  // _SELECTIO_WEBRECORDCONFIG_H__