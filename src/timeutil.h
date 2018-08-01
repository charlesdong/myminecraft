#ifndef TIME_H_
#define TIME_H_

// Originally named "time.h" but changed to "timeutil.h" to prevent conflict with <time.h>.

struct Time
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

Time getTime();

#endif