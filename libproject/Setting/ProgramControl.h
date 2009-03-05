#ifndef _SETTING_PROGRAMCONTROL_H__
#define _SETTING_PROGRAMCONTROL_H__

#include <settingitem.h>
#include <configitem.h>
#include <utility\strutility.h>
#include <map>

class ProgramControl  : public SettingItem , public ConfigItem {
public:
	ProgramControl(void);
	~ProgramControl(void);

public:
		// 应用程序的属性
	typedef struct _tagFileInfo {
	}FILEINFO;
public:
	// 检测应用程序
	bool check(const strutility::_tstring & fullpath);


	// 增加一个应用程序项
	int addItem(const strutility::_tstring &fullpath);
	int removeitem(const strutility::_tstring &fullpath);

	// 枚举项
	int getFirstItem(strutility::_tstring *name, FILEINFO**);
	int getNextItem(const strutility::_tstring & cur, strutility::_tstring *name, FILEINFO**);
public:
	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * item_root);
private:

	typedef std::map<strutility::_tstring, FILEINFO * > PROGRAM_INFO;
	PROGRAM_INFO data_;
};

#endif  // _SETTING_PROGRAMCONTROL_H__
