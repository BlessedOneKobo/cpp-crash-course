#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/time.h>

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
	TimerClass(const char* name) {
		auto name_len = strlen(name);
		if (name_len == 0) {
			throw std::runtime_error{ "name cannot have a length of zero(0)." };
		}
		label = new char[name_len + 1];
		std::strncpy(label, name, name_len);
	}

	TimerClass(const TimerClass& other) {
		if (this == &other) return;
		
		timestamp = other.timestamp;
		auto other_label_len = strlen(other.label);
		// 6 is for "_copy" postfix and null character
		label = new char[other_label_len + 6];
		std::strncpy(label, other.label, other_label_len);
		std::strncpy(label + other_label_len, "_copy", 6);
		printf("[%s] copy constructed from [%s]\n", label, other.label);
	}

	TimerClass(TimerClass&& other) {
		if (this == &other) return;

		timestamp = other.timestamp;
		auto other_label_len = strlen(other.label);
		delete[] label;
		label = new char[other_label_len + 6];
		std::strncpy(label, other.label, other_label_len);
		std::strncpy(label + other_label_len, "_move", 6);

		other.timestamp.tv_sec  = 0;
		other.timestamp.tv_usec = 0;
		printf("[%s] move constructed from [%s]\n", label, other.label);
		delete[] other.label;
	}

	TimerClass& operator=(const TimerClass& other) {
		if (this == &other) return *this;

		timestamp = other.timestamp;
		auto other_label_len = strlen(other.label);
		label = new char[other_label_len + 6];
		std::strncpy(label, other.label, other_label_len);
		std::strncpy(label + other_label_len, "_copy", 6);
		printf("[%s] copy assigned from [%s]\n", label, other.label);
		return *this;
	}

	TimerClass& operator=(TimerClass&& other) {
		if (this == &other) return *this;
		
		timestamp = other.timestamp;
		auto other_label_len = strlen(other.label);
		label = new char[other_label_len + 6];
		std::strncpy(label, other.label, other_label_len);
		std::strncpy(label + other_label_len, "_move", 6);

		other.timestamp.tv_sec  = 0;
		other.timestamp.tv_usec = 0;
		printf("[%s] move assigned from [%s]\n", label, other.label);
		delete[] other.label;
		return *this;
	}

	~TimerClass() {
		// object is in a "moved from" state
		if (timestamp.tv_sec == 0 && timestamp.tv_usec == 0) return;

		TimeStamp current;
		current -= timestamp;
		printf("[%s] destructed after ", label);
		if (current.tv_sec > 0) {
			printf("%ld second(s)\n", current.tv_sec);
		} else {
			printf("%ld microsecond(s)\n", current.tv_usec);
		}

		delete[] label;
	}
private:
	TimeStamp timestamp;
	char* label{ nullptr };
};
