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


//class time {
//public:
//	time(const TCAR *time);
//	time(const struct tm *t);
//
//	void getlocaltime();
//	time_t getseconds();
//private:
//	int year_;
//	int month_;
//	int day_;
//	int hour_;
//	int minutes_;
//	int sec_;
//};
//
//class timespan {
//};

};

#endif  // _UTILITY_TIMEUTILITY_H__