#include "stdafx.h"
#include "./timeutility.h"
#include <assert.h>

namespace timeutility {

//float timespan_days(struct tm *t1, struct tm * t2) {
//	time_t s1 = mktime(t1);
//	time_t s2 = mktime(t2);
//	return static_cast<float>((s1 - s2) / (24 * 60 * 60.0));
//}
//float timespan_hours(struct tm *t1, struct tm * t2) {
//	time_t s1 = mktime(t1);
//	time_t s2 = mktime(t2);
//	return static_cast<float>((s1 - s2) / (60 * 60.0));
//}
//float timespan_mintues(struct tm *t1, struct tm * t2) {
//	time_t s1 = mktime(t1);
//	time_t s2 = mktime(t2);
//	return static_cast<float>((s1 - s2) / ( 60.0));
//}
//float timespan_seconds(struct tm *t1, struct tm * t2) {
//	time_t s1 = mktime(t1);
//	time_t s2 = mktime(t2);
//	return (float)(s1 - s2);
//}

FILETIME ft_from_tm(const tm &t) {
	SYSTEMTIME st = {0};
	st.wYear = t.tm_mday;
	st.wMonth = t.tm_mon;
	st.wDay = t.tm_mday;
	st.wDayOfWeek = t.tm_wday;
	st.wHour = t.tm_hour;
	st.wMinute  = t.tm_min;
	st.wSecond = t.tm_sec;
	st.wMilliseconds = 0;

	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	return ft;
}

// convert 1999-01-01 12:12:00
// convert 1999-1-1  12:12:00
struct tm tmfromstring(const TCHAR * timestr) {
	struct tm t;
	TCHAR *p;
	
	// 确定年月日
	t.tm_year = strtol(timestr, &p, 10);
	assert (NULL != p);
	t.tm_mon = strtol(p+1, &p, 10);
	assert (NULL != p);
	t.tm_mday = strtol(p+1, &p, 10);

	// 确定时分秒
	if (NULL != p) t.tm_hour = strtol(p+1, &p, 10); else t.tm_hour = 0;
	if (NULL != p) t.tm_min = strtol(p+1, &p, 10); else t.tm_min  = 0;
	if (NULL != p) t.tm_sec = strtol(p+1, &p, 10); else t.tm_sec = 0;

	assert (t.tm_hour >= 0 && t.tm_hour < 24);
	assert (t.tm_min >= 0 && t.tm_min < 60);
	assert (t.tm_sec >= 0 && t.tm_sec < 60);
	return t;
}

TCHAR * USFormatTime(SYSTEMTIME  ft, TCHAR *buffer, int len) {
	if (ft.wHour <= 12) {
		_snprintf(buffer, len, "%02d:%02d am %02d/%02d/%04d", ft.wHour, ft.wMinute, ft.wMonth, ft.wDay, ft.wYear);
	} else {
		_snprintf(buffer, len, "%02d:%02d pm %02d/%02d/%04d", ft.wHour - 12, ft.wMinute, ft.wMonth, ft.wDay, ft.wYear);
	}

	return buffer;
}

TCHAR * USFormatTime(FILETIME ft, TCHAR * buffer, int len) {
	SYSTEMTIME st;
	FileTimeToSystemTime(&ft, &st);
	return USFormatTime(st, buffer, len);
}

}; // namespace 