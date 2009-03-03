#ifndef _COMMON_INCLUDE_SEARCHENGINE_DEFINE_H__
#define _COMMON_INCLUDE_SEARCHENGINE_DEFINE_H__

#include <tchar.h>
#include <assert.h>

#define SEARCHENGINE_GOOGLE			0x00000001
#define SEARCHENGINE_NAME_GOOGLE			TEXT("Google")
#define SEARCHENGINE_NAME_GOOGLE_LEN  6

#define SEARCHENGINE_YAHOO				0x00000002
#define SEARCHENGINE_NAME_YAHOO			TEXT("Yahoo")
#define SEARCHENGINE_NAME_YAHOO_LEN	5

#define SEARCHENGINE_BAIDU				0x00000003
#define SEARCHENGINE_NAME_BAIDU				TEXT("Baidu")
#define SEARCHENGINE_NAME_BAIDU_LEN		5


#define SEARCHENGINE_NAME_UNKNOWN		0xFFFFFFFF
#define SEARCHENGINE_NAME_NULL				TEXT("No Search Engine")
#define SEARCHENGINE_NAME_NULL_LEN		16

#define SEARCHENGINE_HOSTNAME_GOOGLE	TEXT("google")
#define SEARCHENGINE_HOSTNAME_YAHOO		TEXT("yahoo")
#define SEARCHENGINE_HOSTNAME_BAIDU		TEXT("baidu")

inline
int getSearchEngineType(const char * name) {
	if (0 == _tcscmp(SEARCHENGINE_HOSTNAME_GOOGLE, name)) {
		return  SEARCHENGINE_GOOGLE;
	} else if (0 == _tcscmp(SEARCHENGINE_HOSTNAME_YAHOO, name)) {
		return SEARCHENGINE_YAHOO;
	} else if (0 == _tcscmp(SEARCHENGINE_NAME_BAIDU, name)) {
		return SEARCHENGINE_BAIDU;
	} else {
		return SEARCHENGINE_NAME_UNKNOWN;
	}
}

inline
int  GetSearchEngineName(const int type, TCHAR ** result) {
	switch (type) {
		case SEARCHENGINE_GOOGLE:
			*result =  SEARCHENGINE_NAME_GOOGLE;
			return SEARCHENGINE_NAME_GOOGLE_LEN;
		case SEARCHENGINE_YAHOO:
			*result =  SEARCHENGINE_NAME_YAHOO;
			return SEARCHENGINE_NAME_YAHOO_LEN ;
		case SEARCHENGINE_BAIDU:
			*result =  SEARCHENGINE_NAME_BAIDU;
			return SEARCHENGINE_NAME_BAIDU_LEN;
		default:
			assert(false);
			*result = SEARCHENGINE_NAME_NULL;
			return SEARCHENGINE_NAME_NULL_LEN;
	}
}


#endif  // _COMMON_INCLUDE_SEARCHENGINE_DEFINE_H__