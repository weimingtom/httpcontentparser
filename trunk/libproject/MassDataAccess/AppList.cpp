#include "stdafx.h"
#include "applist.h"
#include <assert.h>

ApplicationList::ApplicationList(void) {
}

ApplicationList::~ApplicationList(void) {
}

bool ApplicationList::check_path(const strutility::_tstring & fullpath) {
    PROGRAM_INFO::iterator iter = data_.find(fullpath);
    if (data_.end() != iter) {
        return true;
    } else {
        return false;
    }
}

int ApplicationList::add_item(const strutility::_tstring &fullpath) {
	if (fullpath.length() == 0) {
		return 0;
	}
    FILEINFO info;
	data_.insert(std::make_pair(fullpath, info));
	return 0;
}

int ApplicationList::remote_item(const strutility::_tstring &fullpath) {
	PROGRAM_INFO::iterator iter = data_.find(fullpath);
	if (data_.end() != iter) {
		data_.erase(iter);
        return 0;
    } else {
        return 1;
    }
}

// ö�ٺ���
int ApplicationList::get_first_item(strutility::_tstring *name, FILEINFO* info) {
	if (data_.size() == 0)
		return -1;
	
	// ��ȡ����
	*name = data_.begin()->first;
	*info = data_.begin()->second;

	return 0;
}
int ApplicationList::get_next_item(const strutility::_tstring & cur, strutility::_tstring *name, FILEINFO* info) {
	assert(cur.length() != 0);

	PROGRAM_INFO::const_iterator iter = data_.upper_bound(cur);
	if (iter != data_.end()) {
		*name = iter->first;
		*info = iter->second;
		return 0;
	} else {
		return -1;
	}
}
