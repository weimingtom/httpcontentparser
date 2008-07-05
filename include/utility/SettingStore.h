#ifndef _UTILITY_SETTING_STORE_H__
#define _UTILITY_SETTING_STORE_H__

#include <string>
#include <map>

// �� xml �ļ��л�ȡ����
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
