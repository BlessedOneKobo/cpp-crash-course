#include <iostream>
#include <sys/time.h>

void delay() {
	for (auto i = 0; i < 100000; i++)
		;
}

struct TimeStamp {
	time_t tv_sec;
	suseconds_t tv_usec;

	TimeStamp() {
		timeval tv;
		gettimeofday(&tv, nullptr);
		tv_sec  = tv.tv_sec;
		tv_usec = tv.tv_usec;
	}

	TimeStamp& operator-=(const TimeStamp& other) {
		tv_sec  -= other.tv_sec;
		tv_usec -= other.tv_usec;
		return *this;
	}
};

struct TimerClass {
	TimerClass() {}

	TimerClass(const TimerClass& other) {
		if (this == &other) return;
		timestamp = other.timestamp;
	}

	TimerClass(TimerClass&& other) {
		if (this == &other) return;
		timestamp = other.timestamp;
		other.timestamp.tv_sec  = 0;
		other.timestamp.tv_usec = 0;
	}

	TimerClass& operator=(const TimerClass& other) {
		if (this == &other) return *this;
		timestamp = other.timestamp;
		return *this;
	}

	TimerClass& operator=(TimerClass&& other) {
		if (this == &other) return *this;
		timestamp = other.timestamp;
		other.timestamp.tv_sec  = 0;
		other.timestamp.tv_usec = 0;
		return *this;
	}

	~TimerClass() {
		delay();

		// object is in a "moved from" state
		if (timestamp.tv_sec == 0 && timestamp.tv_usec == 0) return;

		TimeStamp current;
		current -= timestamp;
		printf("destructed after ");
		if (current.tv_sec > 0) {
			printf("%ld second(s)\n", current.tv_sec);
		} else {
			printf("%ld microsecond(s)\n", current.tv_usec);
		}
	}
private:
	TimeStamp timestamp;
};
