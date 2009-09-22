#ifndef  _APPLIST_H__
#define _APPLIST_H__

#include <utility\strutility.h>
#include <map>

class ApplicationList   {
public:
	ApplicationList(void);
	~ApplicationList(void);

public:
		// 应用程序的属性
	typedef struct _tagFileInfo {
	}FILEINFO;
public:

	// 增加一个应用程序项
	int add_item(const strutility::_tstring &fullpath);
	int remote_item(const strutility::_tstring &fullpath);

	// 枚举项
    // 枚举的顺序不会按照插入的顺序
    // 而是按照字典顺序进行枚举
	int get_first_item(strutility::_tstring *name, FILEINFO*);
	int get_next_item(const strutility::_tstring & cur, strutility::_tstring *name, FILEINFO*);

    int get_item_num() const { return data_.size();}

    bool check_path(const strutility::_tstring & fullpath);
private:
	typedef std::map<strutility::_tstring, FILEINFO > PROGRAM_INFO;
	PROGRAM_INFO data_;
};

#endif  // _APPLIST_H__