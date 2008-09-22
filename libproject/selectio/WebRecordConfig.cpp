#include "StdAfx.h"
#include ".\webrecordconfig.h"

#include <tinyXML\tinyxml.h>
#include <webcontenttype.h>
#include <time.h>
#include <stdio.h>

WebRecordConfig::WebRecordConfig(void) {
	but_cnt_ = 0;
}

WebRecordConfig::~WebRecordConfig(void) {
	flush();
}


// 此函数并不会直接将它加入到文件当中， 他会分别等积累到一定程度之后再加入
int WebRecordConfig::addItem(const TCHAR * path, const int check_result, const int content_type) {
	// 获取时间
	struct tm   *newTime;
    time_t      szClock;
	time( &szClock );
	newTime = localtime( &szClock );

	// format time
	TCHAR buffer[MAX_PATH];
	_sntprintf(buffer, MAX_PATH, "%d-%d-%d %d:%d:%d",
		newTime->tm_year, newTime->tm_mon, newTime->tm_yday, 
		newTime->tm_hour, newTime->tm_min, newTime->tm_sec);

	RecordItem item;
	item.path = path;
	item.time = buffer;
	
	addToBufferSet(item, check_result, content_type);
	
	bufferedFlush();
	return 0;
}

void WebRecordConfig::addToBufferSet(const RecordItem &item,  const int check_result, const int content_type) {
	BUFFER_RECORD_SET *bufferSet = getCorrectBufferSet(check_result, content_type );
	bufferSet->insert(item);
}

void WebRecordConfig::bufferedFlush() {
	but_cnt_++;
	
	// 如果没到次数， 直接返回
	if (max_buf_count_ > but_cnt_)
		return;

	// 否则写入文件
	flush();
}

// 将配置写入文件
void WebRecordConfig::flush() {
	// 获取到RecordFile的文件名

	// 如果文件不存在则创建一个
	// 打开文件
	TCHAR filename[MAX_PATH];
	TiXmlDocument doc(filename);
	// if (access(filename, 0)
	TiXmlElement * root = doc.RootElement();

	// 写入文件
	getNormalImageRoot(root);
	getPornImageRoot(root);
	getUnknownImageRoot(root);
	getNormalTextRoot(root);
	getPornTextRoot(root);
	getUnknownTextRoot(root);
}

namespace {
const TCHAR * contentCheckResult(const int result) {
	switch (result) {
		case CONTENT_CHECK_PORN:
			return REPOS_TYPE_PORN;
		case CONTENT_CHECK_NORMAL:
			return REPOS_TYPE_NORMAL;
		case CONTENT_CHECK_UNKNOWN:
			return REPOS_TYPE_UNKNOWN;
		default:
			assert(false);
			return NULL;
	}
}

const TCHAR *contentType(const int type) {
	if (isText(type)) {
		return REPOS_TEXT_ITEM;
	} else if (isImage(type)) {
		return REPOS_IMAGE_ITEM;
	}

	assert(false);
	return "";
}
};


void WebRecordConfig::writeNormalImage(TiXmlElement * root) {
	TiXmlElement * normal_image_root = getNormalImageRoot(root);
	writeItems(&image_normal_set_, CONTYPE_PNG, normal_image_root);
}

void WebRecordConfig::writePornImage(TiXmlElement * root) {
	TiXmlElement * porn_image_root = getNormalImageRoot(root);
	writeItems(&image_porn_set_, CONTYPE_PNG, porn_image_root);
}
void WebRecordConfig::writeUnknownImage(TiXmlElement * root) {
	TiXmlElement * unknown_image_root = getNormalImageRoot(root);
	writeItems(&image_unknown_set_, CONTYPE_PNG, unknown_image_root);
}

void WebRecordConfig::writePornText(TiXmlElement * root) {
	TiXmlElement * unknown_text_root = getNormalImageRoot(root);
	writeItems(&text_unknown_set_, CONTYPE_PNG, unknown_text_root);
}
void WebRecordConfig::writeNormalText(TiXmlElement * root) {
	TiXmlElement * unknown_text_root = getNormalImageRoot(root);
	writeItems(&text_unknown_set_, CONTYPE_PNG, unknown_text_root);
}
void WebRecordConfig::writeUnknownText(TiXmlElement * root) {
	TiXmlElement * unknown_text_root = getNormalImageRoot(root);
	writeItems(&text_unknown_set_, CONTYPE_PNG, unknown_text_root);
}

WebRecordConfig::BUFFER_RECORD_SET*
WebRecordConfig::getCorrectBufferSet(const int check_result, const int content_type) {
	if (isText(content_type)) {
		switch (check_result) {
			case CONTENT_CHECK_PORN:
				return &text_porn_set_;
			case CONTENT_CHECK_NORMAL:
				return &text_normal_set_;
			case CONTENT_CHECK_UNKNOWN:
				return &text_unknown_set_;
			default:
				assert(false);
				return &unknown_at_all_;
		}
	} else if (isImage(content_type)) {
		switch (check_result) {
			case CONTENT_CHECK_PORN:
				return &image_porn_set_;
			case CONTENT_CHECK_NORMAL:
				return &image_normal_set_;
			case CONTENT_CHECK_UNKNOWN:
				return &image_unknown_set_;
			default:
				assert(false);
				return &unknown_at_all_;
		}
	} else {
		assert (false);
		return &unknown_at_all_;
	}
}


// 写入文件并清空
void WebRecordConfig::writeItems(BUFFER_RECORD_SET *itemsets, const int content_type,  TiXmlElement * image_root) {
	assert (itemsets != NULL);
	
	const TCHAR * node_name = contentType(content_type);
	// enumerate
	BUFFER_RECORD_SET::const_iterator iter = itemsets->begin();
	for (; iter != itemsets->end(); ++iter) {
		TiXmlElement * item_node = new TiXmlElement(node_name);
		item_node->SetAttribute(REPOS_ITEM_ATTR_PATH, iter->path.c_str());
		item_node->SetAttribute(REPOS_ITEM_ATTR_TIME, iter->time.c_str());
		image_root->LinkEndChild(item_node);
	}

	itemsets->clear();
}


//========================================================
// 从xml中获取根结点，如果获取不到，则新建
TiXmlElement * WebRecordConfig::getNormalImageRoot(TiXmlElement * root) {
	assert (NULL != root);
	
	return NULL;
}
TiXmlElement * WebRecordConfig::getPornImageRoot(TiXmlElement * root) {
	assert (NULL != root);
	return NULL;
}
TiXmlElement * WebRecordConfig::getUnknownImageRoot(TiXmlElement * root) {
	assert (NULL != root);
	return NULL;
}
TiXmlElement * WebRecordConfig::getNormalTextRoot(TiXmlElement * root) {
	assert (NULL != root);
	return NULL;
}
TiXmlElement * WebRecordConfig::getPornTextRoot(TiXmlElement * root) {
	assert (NULL != root);
	return NULL;
}
TiXmlElement * WebRecordConfig::getUnknownTextRoot(TiXmlElement * root) {
	assert (NULL != root);
	return NULL;
}

// 检测XML文件是否合法
// 首先检查文件是否存在，如果不存在则创建一个, 并添加必要信息
// 如果没有相应的信息，XML文件不合法，则重新修改
void WebRecordConfig::validateConfig(const TCHAR *filename) {
}