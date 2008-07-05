#include "StdAfx.h"
#include ".\settingstore.h"

XERCES_CPP_NAMESPACE_USE 

const std::string SettingStore::NO_ATTRIBUTE = "";

SettingStore::SettingStore(void) {
}

SettingStore::~SettingStore(void) {
}

void SettingStore::load(const std::string &filename) {
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& ) {
		// Do your failure processing here
		return;
	}
	XMLPlatformUtils::Terminate();
}
void SettingStore::store(const std::string &filename) {
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException&) {
		// Do your failure processing here
		return ;
	}

	XMLPlatformUtils::Terminate();
}
std::string SettingStore::QuerySetting(const std::string & attribute_name) {
	SETTINGS::iterator iter = setting_.find(attribute_name);
	if (iter != setting_.end()) {
		return iter->second; 
	} else {
		return std::string(NO_ATTRIBUTE);
	}
}