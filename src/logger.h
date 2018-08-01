#ifndef LOGGER_H_
#define LOGGER_H_

enum LogLevel
{
	INFO,
	WARNING,
	ERROR,
	FATAL
};

class Logger
{
private:
	char filename[50];
	const char * getLevelStr(LogLevel level) const;
public:
	Logger();
	void log(LogLevel level, const char * message);
};

#endif