#ifndef _UTILITY_TIMEUTILITY_H__
#define _UTILITY_TIMEUTILITY_H__

#include <stdlib.h>
#include <time.h>

namespace timeutility {
//
//float timespan_days(struct tm *t1, struct tm * t2);
//float timespan_hours(struct tm *t1, struct tm * t2);
//float timespan_mintues(struct tm *t1, struct tm * t2);
//float timespan_seconds(struct tm *t1, struct tm * t2);

struct tm tmfromstring(const TCHAR * timestr);

TCHAR * USFormatTime(SYSTEMTIME  ft, TCHAR *buffer, int len);

};

#endif  // _UTILITY_TIMEUTILITY_H__