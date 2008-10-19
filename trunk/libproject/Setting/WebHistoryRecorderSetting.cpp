#include "StdAfx.h"
#include "webhistoryrecordersetting.h"

WebHistoryRecorderSetting::WebHistoryRecorderSetting(void) {
	defaultSetting();
}

WebHistoryRecorderSetting::~WebHistoryRecorderSetting(void) {
}

void WebHistoryRecorderSetting::defaultSetting() {
	enabled_ = true;

	recordPornPage_ = true;
	recordPornImage_ = true;
	recordPornWebsite_ = true;

	recordImage_ = false;
	recordPage_ = false;
	recordWebsite_ = false;

	SettingItem::defaultSetting();
}

bool WebHistoryRecorderSetting::recordAllPages() const {
	if (isEnabled() ) {
		return recordPage_;
	} else {
		return false;
	}
}


bool WebHistoryRecorderSetting::recordAllImage() const	{
	if (isEnabled() ) {
		return recordImage_;
	} else {
		return false;
	}
}
bool WebHistoryRecorderSetting::recordAllWebsite() const {
	if (isEnabled() ) {
		return recordWebsite_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornImage() const	{
	if (isEnabled() ) {
		return recordPornImage_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornPages() const	{
	if (isEnabled() ) {
		return recordPornPage_;
	} else {
		return false;
	}
}

bool WebHistoryRecorderSetting::recordPornWebsite() const {
	if (isEnabled() ) {
		return recordPornWebsite_;
	} else {
		return false;
	}
}

//=========================================================
// XML
int WebHistoryRecorderSetting::parseConfig(TiXmlElement * item_root) {
	getWebHistoryRecorder(item_root);
	return 0;
}
int WebHistoryRecorderSetting::saveConfig(TiXmlElement * item_root) {
	saveWebHistory(item_root);
	return 0;
}


	// 设置它是否可用
	// enableWebHistoryRecord(ele->Attribute(CONFIG_CONST_ENABLE));

//=========================================================
// WebHistory
int WebHistoryRecorderSetting::enableWebHistoryRecord(const TCHAR *isenable) {
	const bool enabled = enabledFromString(isenable);
	enable(enabled);
	return 0;
}

int WebHistoryRecorderSetting::setWebHistoryRecord(const TCHAR *type, const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE)) {
		recordPornPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE)) {
		recordAllPages(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_IMAGE)) {
		recordAllImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_IMAGE)) {
		recordPornImage(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE)) {
		recordAllWebsite(enabled);
	} else if (0 == _tcscmp(type, CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE)) {
		recordPornWebsite(enabled);
	} else {
	}
	return 0;
}



int WebHistoryRecorderSetting::setWebHistoryAutoClean(TiXmlElement * element) {
	assert (element && _tcscmp(element->Value(), CONFIG_APPSET_AUTOCLEAR) == 0);
	enableWebHistoryAutoClean(element->Attribute(CONFIG_CONST_ENABLE));
	setWebHistoryAutoCleanTimespan(element->Attribute(CONSIG_CONST_TIMESPAN));
	setWebHistoryAutoCleanTimeScale(element->Attribute(CONFIG_CONST_MAX), element->Attribute(CONFIG_CONST_MIN));
	setWebHistoryLastCleanTiime(element->Attribute(CONFIG_CONST_LASTTIME));
	return 0;
}

int WebHistoryRecorderSetting::enableWebHistoryAutoClean(const TCHAR *enable) {
	const bool enabled = enabledFromString(enable);
	getAutoclean()->enable(enabled);
	return 0;
}

int WebHistoryRecorderSetting::setWebHistoryAutoCleanTimespan(const TCHAR *timespan) {
	getAutoclean()->setTimespan(_ttoi(timespan));
	return 0;
}

int WebHistoryRecorderSetting::setWebHistoryAutoCleanTimeScale(const TCHAR *maxt, const TCHAR * mint) {
	const int low_bound = _ttoi(mint);
	const int upper_bound = _ttoi(maxt);
	getAutoclean()->setScale(low_bound, upper_bound);
	return 0;
}


int WebHistoryRecorderSetting::setWebHistoryLastCleanTiime(const TCHAR * lastclean) {
	getAutoclean()->setLastTime(lastclean);
	return 0;
}
int WebHistoryRecorderSetting::getWebHistoryRecorder(TiXmlElement *ele) {
	assert (0 == _tcscmp(ele->Value(), CONFIG_ITEM_APPSET_WEBHISTORY));

	// 设置它是否可用
	enableWebHistoryRecord(ele->Attribute(CONFIG_CONST_ENABLE));
	
	TiXmlNode * node = ele->FirstChild();
	while (NULL != node) {
		TiXmlElement *ele = node->ToElement();
		if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_APPSET_WEBHISTORY_CONTENT)) {
			setWebHistoryRecord(ele->Attribute(CONFIG_CONST_TYPPE), ele->Attribute(CONFIG_CONST_ENABLE));
		} else if (NULL != ele && 0 == _tcscmp(ele->Value(), CONFIG_APPSET_AUTOCLEAR)) {
			setWebHistoryAutoClean(ele);
		}

		node = node->NextSibling();
	}
	return 0;
}

// 保存
int WebHistoryRecorderSetting::saveWebHistory(TiXmlElement * app_root) {
	TiXmlElement * webhistory_root = new TiXmlElement(CONFIG_ITEM_APPSET_WEBHISTORY); 
	webhistory_root->SetAttribute(CONFIG_CONST_NAME,  enabledFromBool( isEnabled()));

	// All Images
	TiXmlElement * allimage = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allimage->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_IMAGE);
	allimage->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordAllImage()));
	webhistory_root->LinkEndChild(allimage);

	TiXmlElement * allpages = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allpages->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE);
	allpages->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordAllPages()));
	webhistory_root->LinkEndChild(allpages);

	TiXmlElement * allwebsite = new TiXmlElement(CONFIG_APPSET_WEBHISTORY_CONTENT); 
	allwebsite->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE);
	allwebsite->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordAllWebsite()));
	webhistory_root->LinkEndChild(allwebsite);

	// Porn
	TiXmlElement * porn_Iimage = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_Iimage->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_IMAGE);
	porn_Iimage->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordPornImage()));
	webhistory_root->LinkEndChild(porn_Iimage);

	TiXmlElement * porn_pages = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_pages->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE);
	porn_pages->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordPornPages()));
	webhistory_root->LinkEndChild(porn_pages);

	TiXmlElement * porn_website = new TiXmlElement( CONFIG_APPSET_WEBHISTORY_CONTENT ); 
	porn_website->SetAttribute(CONFIG_CONST_TYPPE, CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE);
	porn_website->SetAttribute(CONFIG_CONST_NAME, enabledFromBool( recordPornWebsite()));
	webhistory_root->LinkEndChild(porn_website);

	TCHAR buffer[MAX_PATH];
	TiXmlElement * autoclean = new TiXmlElement( CONFIG_APPSET_AUTOCLEAR ); 
	autoclean->SetAttribute(CONFIG_CONST_MAX, _itot(getAutoclean()->getRangeMax(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_MIN, _itot(getAutoclean()->getRangeMin(), buffer, 10));
	autoclean->SetAttribute(CONSIG_CONST_TIMESPAN, _itot(getAutoclean()->getTimespan(), buffer, 10));
	autoclean->SetAttribute(CONFIG_CONST_LASTTIME, getAutoclean()->getLastTime());
	webhistory_root->LinkEndChild(autoclean);

	app_root->LinkEndChild(webhistory_root);
	return 0;
}