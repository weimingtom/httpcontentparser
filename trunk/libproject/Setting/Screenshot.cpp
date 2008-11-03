#include "StdAfx.h"
#include ".\Screenshot.h"


void Screenshot::defaultSetting() {
	calcugraph_.initialize();
	enable(false);
	setTimeSpan(60 * 20); // 20 mins

	SettingItem::defaultSetting();
}


void Screenshot::setTimeSpan(const int seconds) {
	setModified(true); 
	calcugraph_.setTimespan(seconds);
}

int Screenshot::getTimeSpan() const {
	return calcugraph_.getTimespan();
}

bool Screenshot::shouldSave() {
	if (false == isEnabled()) {
		return false;
	}
	return calcugraph_.trySwitch();
}

//==================================
// protected memberr


//===================================
// constructors and deconstructors
Screenshot::Screenshot(void) {
	defaultSetting();
}

Screenshot::~Screenshot(void) {
}


// XML
int Screenshot::parseConfig(TiXmlElement * item_root) {
	getScreenshot(item_root);
	return 0;
}
TiXmlElement * Screenshot::saveConfig(TiXmlElement * item_root) {
	return saveScreensave(item_root);
}


//==========================================================
// 保存屏幕保存功能
TiXmlElement * Screenshot::saveScreensave(TiXmlElement * root) {
	TCHAR buffer[MAX_PATH];
	TiXmlElement * rule_root = new TiXmlElement(CONFIG_ITEM_APPSET_SCREENSAVER);
	rule_root->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(isSettingEnabled()));

	_sntprintf(buffer, MAX_PATH, TEXT("%d"), calcugraph_.getTimespan());
 	rule_root->SetAttribute(CONSIG_CONST_TIMESPAN, buffer);

	
	TiXmlElement * autoclean = new TiXmlElement( CONFIG_APPSET_AUTOCLEAR ); 
	autoclean->SetAttribute(CONFIG_CONST_MAX, _itot(getAutoClean()->getRangeMax(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_MIN, _itot(getAutoClean()->getRangeMin(), buffer, 10));
	autoclean->SetAttribute(CONSIG_CONST_TIMESPAN, _itot(getAutoClean()->getTimespan(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_LASTTIME, getAutoClean()->getLastTime());
	autoclean->SetAttribute(CONFIG_CONST_ENABLE, enabledFromBool(getAutoClean()->isEnable()));
	rule_root->LinkEndChild(autoclean); 

	root->LinkEndChild(rule_root);
	return rule_root;
}


//===============================================
// Screensave
int Screenshot::getScreenshot(TiXmlElement * ele){
	enableScreenshot(ele->Attribute(CONFIG_CONST_ENABLE));
	setScreenshotTimespan(ele->Attribute(CONSIG_CONST_TIMESPAN));
	setScreenshotAutoClean(ele);
	return 0;
}
int Screenshot::enableScreenshot(const TCHAR *isenable){
	const bool enabled = enabledFromString(isenable);
	enable(enabled);
	return 0;
}

int Screenshot::setScreenshotTimespan(const TCHAR *timespan){
	setTimeSpan(atoi(timespan));
	return 0;
}


int Screenshot::setScreenshotAutoClean(TiXmlElement * ele) {
	TiXmlNode *node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement * element = node->ToElement();
		if (element && _tcscmp(element->Value(), CONFIG_APPSET_AUTOCLEAR) == 0) {
			enableScreenshotAutoClean(element->Attribute(CONFIG_CONST_ENABLE));
			setScreenshotAutoCleanTimespan(element->Attribute(CONSIG_CONST_TIMESPAN));
			const char * p = element->Attribute(CONFIG_CONST_MAX);
			setScreenshotAutoCleanTimeScale(element->Attribute(CONFIG_CONST_MAX), element->Attribute(CONFIG_CONST_MIN));
			setScreenshotLastCleanTiime(element->Attribute(CONFIG_CONST_LASTTIME));
		}
		node = node->NextSibling();
	}
	return 0;
}

//== 设置ScreenSaveAutoClean的
int Screenshot::setScreenshotLastCleanTiime(const TCHAR * lastclean) {
	getAutoClean()->setLastTime(lastclean);
	return 0;
}

int Screenshot::enableScreenshotAutoClean(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	getAutoClean()->enable(enabled);
	return 0;
}
int Screenshot::setScreenshotAutoCleanTimespan(const TCHAR *timespan) {
	getAutoClean()->setTimespan(_ttoi(timespan));
	return 0;
}

int Screenshot::setScreenshotAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint) {
	const int low_bound = _ttoi(mint);
	const int upper_bound = _ttoi(maxt);
	getAutoClean()->setScale(low_bound, upper_bound);
	return 0;
}
