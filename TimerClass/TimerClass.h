#include <sys/time.h>

struct TimeStamp {
	TimeStamp() {
		timeval tv;
		gettimeofday(tv, nullptr);
		tv_sec  = tv.tv_sec;
		tv_usec = tv.tv_usec;
	}
private:
	time_t tv_sec;
	suseconds_t tv_usec;
};

struct TimerClass {
	TimerClass() {}
private:
	TimeStamp timestamp;
};
