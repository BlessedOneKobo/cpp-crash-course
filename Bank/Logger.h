#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>

struct Logger {
	virtual void log_transfer(long from, long to, double amount) const = 0;
};

struct ConsoleLogger : Logger {
	ConsoleLogger(const char* prefix) : prefix{ prefix } {}
	
	void log_transfer(long from, long to, double amount) const override {
		printf("[%s] %ld -> %ld: %f\n", prefix, from, to, amount);
	}
private:
	const char* prefix;
};

struct FileLogger : Logger {
	void log_transfer(long from, long to, double amount) const override {
		printf("[file] %ld,%ld,%f\n", from, to, amount);
	}
};

#endif
