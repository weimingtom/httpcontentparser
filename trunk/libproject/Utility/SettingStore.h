#ifndef _UTILITY_SETTING_STORE_H__
#define _UTILITY_SETTING_STORE_H__

#include <string>
#include <map>

// 从 xml 文件中获取规则
class SettingStore {
public:
	SettingStore();
	~SettingStore();

	std::string QuerySetting(const std::string & attribute_name);
	void load(const std::string &filename);
	void store(const std::string &filename);

	static const std::string NO_ATTRIBUTE;
private:
	typedef std::map<std::string, std::string> SETTINGS;
	SETTINGS setting_;
};


#endif  // _UTILITY_SETTING_STORE_H__
