#include "TimerClass.h"
#include <utility>

int main() {
	TimerClass tc;
	TimerClass tc_copy{ tc };
	TimerClass tc_copy_assign = tc;
	TimerClass tc_move{ std::move(tc) };
	TimerClass tc_move_assign = std::move(tc_copy);
}
