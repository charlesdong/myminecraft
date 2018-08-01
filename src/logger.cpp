#include "logger.h"
#include <cstring>
#include <fstream>
#include <cassert>
#include "timeutil.h"

Logger::Logger()
{
	strcpy_s(filename, "log.txt");
}

void Logger::log(LogLevel level, const char * log)
{
	std::ofstream fout;
	fout.open(filename, std::ios_base::app);
	Time time = getTime();
	fout << "[" << time.hour << ":" << time.minute << ":" << time.second << "]["
		<< getLevelStr(level) << "] "
		<< log << "\n";
}

const char * Logger::getLevelStr(LogLevel level) const
{
	switch (level)
	{
	case INFO:
		return "INFO";
	case WARNING:
		return "WARNING";
	case ERROR:
		return "ERROR";
	case FATAL:
		return "FATAL";
	default:
		assert("Invalid log level string" && false);
		return nullptr;
	}
}