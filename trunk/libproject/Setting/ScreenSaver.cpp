#include "StdAfx.h"
#include ".\screensaver.h"


void ScreenSaver::defaultSetting() {
	calcugraph_.initialize();
	enable(false);
	setTimeSpan(60 * 20); // 20 mins

	SettingItem::defaultSetting();
}


void ScreenSaver::setTimeSpan(const int seconds) {
	calcugraph_.setTimespan(seconds);
}

int ScreenSaver::getTimeSpan() const {
	return calcugraph_.getTimespan();
}

bool ScreenSaver::shouldSave() {
	if (false == isEnabled()) {
		return false;
	}
	return calcugraph_.trySwitch();
}

//==================================
// protected memberr


//===================================
// constructors and deconstructors
ScreenSaver::ScreenSaver(void) {
	defaultSetting();
}

ScreenSaver::~ScreenSaver(void) {
}


// XML
int ScreenSaver::parseConfig(TiXmlElement * item_root) {
	getScreensave(item_root);
	return 0;
}
int ScreenSaver::saveConfig(TiXmlElement * item_root) {
	saveScreensave(item_root);
	return 0;
}


//==========================================================
// 保存屏幕保存功能
int ScreenSaver::saveScreensave(TiXmlElement * root) {
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_ITEM_APPSET_SCREENSAVER);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isEnabled()));
	rule_root->SetAttribute(CONSIG_CONST_TIMESPAN, TEXT("10"));

	TiXmlElement * auto_save = new TiXmlElement(CONFIG_APPSET_AUTOCLEAR);
	auto_save->SetAttribute(CONFIG_CONST_ENABLE,	enabledFromBool(isEnabled()));
	auto_save->SetAttribute(CONFIG_CONST_MIN,		enabledFromBool(isEnabled()));
	auto_save->SetAttribute(CONFIG_CONST_MAX,		enabledFromBool(isEnabled()));
	auto_save->SetAttribute(CONSIG_CONST_TIMESPAN,	enabledFromBool(isEnabled()));
	rule_root->LinkEndChild(auto_save);

	TCHAR buffer[MAX_PATH];
	TiXmlElement * autoclean = new TiXmlElement( CONFIG_APPSET_AUTOCLEAR ); 
	autoclean->SetAttribute(CONFIG_CONST_MAX, _itot(getAutoClean()->getRangeMax(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_MIN, _itot(getAutoClean()->getRangeMin(), buffer, 10));
	autoclean->SetAttribute(CONSIG_CONST_TIMESPAN, _itot(getAutoClean()->getTimespan(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_LASTTIME, getAutoClean()->getLastTime());
	rule_root->LinkEndChild(autoclean);

	root->LinkEndChild(rule_root);
	return 0;
}

//===============================================
// Screensave
int ScreenSaver::getScreensave(TiXmlElement * ele){
	enableScreensave(ele->Attribute(CONFIG_CONST_ENABLE));
	setScreensaveTimespan(ele->Attribute(CONSIG_CONST_TIMESPAN));
	setScreensaveAutoClean(ele);
	return 0;
}
int ScreenSaver::enableScreensave(const TCHAR *isenable){
	const bool enabled = enabledFromString(isenable);
	enable(enabled);
	return 0;
}

int ScreenSaver::setScreensaveTimespan(const TCHAR *timespan){
	setTimeSpan(atoi(timespan));
	return 0;
}


int ScreenSaver::setScreensaveAutoClean(TiXmlElement * ele) {
	TiXmlNode *node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if (element && _tcscmp(element->Value(), CONFIG_APPSET_AUTOCLEAR) == 0) {
			enableScreenSaveAutoClean(element->Attribute(CONFIG_CONST_ENABLE));
			setScreensaveAutoCleanTimespan(element->Attribute(CONSIG_CONST_TIMESPAN));
			setScreensaveAutoCleanTimeScale(element->Attribute(CONFIG_CONST_MAX), element->Attribute(CONFIG_CONST_MIN));
			setScreensaveLastCleanTiime(element->Attribute(CONFIG_CONST_LASTTIME));
		}
		node = node->NextSibling();
	}
	return 0;
}

//== 设置ScreenSaveAutoClean的
int ScreenSaver::setScreensaveLastCleanTiime(const TCHAR * lastclean) {
	getAutoClean()->setLastTime(lastclean);
	return 0;
}

int ScreenSaver::enableScreenSaveAutoClean(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	getAutoClean()->enable(enabled);
	return 0;
}
int ScreenSaver::setScreensaveAutoCleanTimespan(const TCHAR *timespan) {
	getAutoClean()->setTimespan(_ttoi(timespan));
	return 0;
}

int ScreenSaver::setScreensaveAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint) {
	const int low_bound = _ttoi(mint);
	const int upper_bound = _ttoi(maxt);
	getAutoClean()->setScale(low_bound, upper_bound);
	return 0;
}
