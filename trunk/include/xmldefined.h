#ifndef _INCLUDE_XML_ELEMENT_DEFINED_H__
#define _INCLUDE_XML_ELEMENT_DEFINED_H__

#include <app_constants.h>

#define CONFIG_ROOT_VALUE					TEXT("config")
#define CONFIG_NODE_RULES					TEXT("rules")
#define CONFIG_NODE_APPSET					TEXT("appsetting")


//======================================================
// 一下是一些常用的常量
#define CONFIG_CONST_NAME					TEXT("name")
#define CONFIG_CONST_TYPPE					TEXT("type")
#define CONFIG_CONST_ENABLE					TEXT("enable")
#define CONFIG_CONST_ENABLE_TRUE			TEXT("true")
#define CONFIG_CONST_ENABLE_FALSE			TEXT("false")
#define CONFIG_CONST_MIN					TEXT("min")
#define	CONFIG_CONST_MAX					TEXT("max")
#define CONSIG_CONST_TIMESPAN				TEXT("timespan")
#define CONFIG_CONST_LASTTIME				TEXT("lastclean")


#define CONFIG_NODE_RULE_ITEM				TEXT("rule")

#define CONFIG_NODE_NAME_BLACKURL			TEXT("blackurl")
#define CONFIG_NODE_NAME_WHITEURL			TEXT("whiteurl")
#define CONFIG_WHITEURL_JUSTPASSED			TEXT("justpass")
#define CONFIG_NODE_URL						TEXT("url")
#define CONFIG_NODE_NAME_SEARCH				TEXT("search")
#define CONFIG_NODE_NAME_IMAGECHECK			TEXT("imagecheck")
#define CONFIG_NODE_NAME_TEXT				TEXT("textrule")

#define CONFIG_NODE_NAME_ONLINETIME			TEXT("onlinetime")
#define CONFIG_NODE_NAME_BLACKTIME			TEXT("blocktime")
#define CONFIG_ONLINETIME_SEPERATE			TEXT("-")


#define CONFIG_NODE_IMAGE_CHECK_ITEM		TEXT("check")
#define CONFIG_NODE_IMAGETYPE				TEXT("imagetype")
#define CONFIG_NODE_IMAGETYPE_BMP			TEXT("bmp")
#define CONFIG_NODE_IMAGETYPE_GIF			TEXT("gif")
#define CONFIG_NODE_IMAGETYPE_PNG			TEXT("png")
#define CONFIG_NODE_IMAGETYPE_JPG			TEXT("jpg")

#define CONFIG_NODE_SEARCH_ENGINES			TEXT("searchengines")
#define CONDIG_NODE_SEARCH_ENGINE_ITEM		TEXT("searchengine")
#define CONFIG_NODE_BLACK_SEARCHWORD		TEXT("blackwords")
#define CONFIG_NODE_BLACK_WORDITEM			TEXT("word")
//#define CONFIG_NODE_BLACK_ENINE

// Autorize
#define CONFIG_ITEM_APPSET_AUTHORIZE			TEXT("authorize")
#define CONFIG_APPSET_AUTHORIZE_USER			TEXT("user")
#define CONFIG_APPSET_AUTHORIZE_NAME			TEXT("username")
#define CONFIG_APPSET_AUTHORIZE_PASSWORD		TEXT("password")
#define CONFIG_APPSET_AUTHORIZE_USERTYPE_SU		TEXT("su")
#define CONFIG_APPSET_AUTHORIZE_USERTYPE_OTHER	TEXT("other")



#define CONFIG_ITEM_APPSET_SYSSETTING		TEXT("syssetting")

// Eyecare
#define CONFIG_ITEM_APPSET_EYECARE			TEXT("eyecare")
#define CONFIG_APPSET_EYECARE_TIME			TEXT("time")
#define CONFIG_APPSET_EYECARE_TIMESPAN		TEXT("timespan")
#define CONFIG_APPSET_EYECARE_EYECARE		TEXT("eyecare_time")
#define CONFIG_APPSET_EYECARE_ENTER			TEXT("enter_time")
#define CONFIG_APPSET_EYECARE_STATE			TEXT("state")
#define CONFIG_APPSET_EYECARE_TIMELEFT		TEXT("timeleft")
#define CONFIG_APPSET_EYECARE_TERM_MODE		TEXT("term_mode")

// WebHistory
#define CONFIG_ITEM_APPSET_WEBHISTORY			TEXT("webhistory")
#define CONFIG_APPSET_WEBHISTORY_CONTENT		TEXT("content")
#define CONFIG_APPSET_WEBHISTORY_ALL_IMAGE		TEXT("all_images")
#define CONFIG_APPSET_WEBHISTORY_PORN_IMAGE		TEXT("porn_images")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBSITE	TEXT("all_website")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBSITE	TEXT("porn_website")
#define CONFIG_APPSET_WEBHISTORY_ALL_WEBPAGE	TEXT("all_webpage")
#define CONFIG_APPSET_WEBHISTORY_PORN_WEBPAGE	TEXT("porn_webpage")

// screenSaver
#define CONFIG_ITEM_APPSET_SCREENSAVER			TEXT("screensave")
#define CONFIG_APPSET_AUTOCLEAR					TEXT("autoclean")

// HOTKEY
#define CONFIG_ITEM_APPSET_HOTKEY				TEXT("hotkeys")
#define CONFIG_APPSET_HOTKEY_ITEM				TEXT("hotkey")
#define CONFIG_HOTKEY_PROP_KEY					TEXT("key")

#define CONFIG_ITEM_MODEL_AUTOSWITCH			TEXT("autoswitch")


inline
bool enabledFromString(const TCHAR *enable) {
	if (NULL != enable) {
		if (0 == _tcscmp(enable, CONFIG_CONST_ENABLE_FALSE)) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

inline
const char * enabledFromBool(const bool enabled) {
	if (true == enabled) {
		return CONFIG_CONST_ENABLE_TRUE;
	} else {
		return CONFIG_CONST_ENABLE_FALSE;
	}
}

#endif // _INCLUDE_XML_ELEMENT_DEFINED_H__