#ifndef _UTILITY_TIMEUTILITY_H__
#define _UTILITY_TIMEUTILITY_H__

#include <stdlib.h>
#include <time.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace timeutility {
//
//float timespan_days(struct tm *t1, struct tm * t2);
//float timespan_hours(struct tm *t1, struct tm * t2);
//float timespan_mintues(struct tm *t1, struct tm * t2);
//float timespan_seconds(struct tm *t1, struct tm * t2);

struct tm tmfromstring(const TCHAR * timestr);

TCHAR * USFormatTime(SYSTEMTIME  ft, TCHAR *buffer, INT_PTR len);
TCHAR * USFormatTime(FILETIME ft, TCHAR * buffer, INT_PTR len);

FILETIME ft_from_tm(const tm &t);

std::string format_ptime_to_timestamp( boost::posix_time::ptime & pt);
};

#endif  // _UTILITY_TIMEUTILITY_H__