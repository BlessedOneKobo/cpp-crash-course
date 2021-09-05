#include "TimerClass.h"
#include <utility>

void delay() {
	TimerClass tc_delay{ "delay" };
	for (auto i = 0; i < 100000; i++)
		;
}

void longer_delay() {
	TimerClass tc_longer_delay{ "longer_delay" };
	for (auto i = 0; i < 100000000; i++)
		;
}

int main() {
	delay();
	longer_delay();
	delay();
	delay();
	delay();
}
