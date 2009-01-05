#ifndef _FILTERSETTING_REGISTERINFO_H__
#define _FILTERSETTING_REGISTERINFO_H__

#include <string>

#define SOFTWARE_EDITION_TRIAL		 0x100000F
#define SOFTWARE_EDITION_REGISTERED  0x1000000

// 用户的注册信息
// 用户信息应该保存在一个文件当中
class RegisterInfo {
public:
	RegisterInfo(void);
	~RegisterInfo(void);

	// 是否已经注册
	bool registered() const {
		return SOFTWARE_EDITION_REGISTERED == edition_type_;
	}

	int getEditionType() const {
		return edition_type_;
	}

	// 注册信息是否成功
	bool registerSoft(const std::string & register_info);
public:
	// 从计算机信息中读取注册信息
	void initialize();
private:
	// 时间日期
	int edition_type_; // 版本内容
};

#endif  // _FILTERSETTING_REGISTERINFO_H__
