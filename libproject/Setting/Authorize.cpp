#include "StdAfx.h"
#include ".\authorize.h"
#include <assert.h>

Authorize::Authorize(void) {
}

Authorize::~Authorize(void) {
}


bool Authorize::setNewPassword(const std::string &password, const int type) {
	assert(password_set_.find(type) == password_set_.end());
	if (password_set_.find(type) == password_set_.end()) {
		password_set_.insert(make_pair(type, password));
		return true;
	} else {
		return false;
	}
}

bool Authorize::checkPassword(const std::string &password, const int type) {
	PASSWORD_MAP::iterator iter = password_set_.find(type);
	assert (iter != password_set_.end());
	if (iter->second == password) {
		return true;
	} else {
		return false;
	}
}

// 如果设置失败返回 false, 成功返回 true
bool Authorize::setPassword(const std::string &password, const std::string &oldword, const int type) {
	if (checkPassword(oldword, type)) {
		password_set_[type] = password;
		return true;
	} else {
		return false;
	}
}