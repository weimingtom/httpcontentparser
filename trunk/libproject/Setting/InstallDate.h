#ifndef _SETTING_INSTALLDATE_H_
#define _SETTING_INSTALLDATE_H_

#include <settingitem.h>
#include <configitem.h>
#include <xmldefined.h>
#include <string>

class InstallDate : public ConfigItem{
public:
	InstallDate(void);
	~InstallDate(void);

public:
	void setInstallDate(const std::string &date) {
		install_date_ = date;
	}
	std::string getInstallDate() const { return install_date_; }

	virtual int parseConfig(TiXmlElement * item_root);
	virtual TiXmlElement *  saveConfig(TiXmlElement * item_root);
private:
	std::string install_date_;
};

#endif  // _SETTING_INSTALLDATE_H_