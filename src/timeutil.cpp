#include <ctime>
#include "timeutil.h"

Time getTime()
{
	time_t timeSys = time(nullptr);
	tm timeStruct;
	localtime_s(&timeStruct, &timeSys);

	Time result;
	result.year = timeStruct.tm_year;
	result.month = timeStruct.tm_mon;
	result.day = timeStruct.tm_mday;
	result.hour = timeStruct.tm_hour;
	result.minute = timeStruct.tm_min;
	result.second = timeStruct.tm_sec;

	return result;
}