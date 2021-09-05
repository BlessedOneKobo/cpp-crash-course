#include "TimerClass.h"
#include <utility>

int main() {
	TimerClass tc{ "tc" };
	TimerClass tc_copy{ tc };
	TimerClass tc_copy_assign = tc_copy;
	TimerClass tc_move{ std::move(tc) };
	TimerClass tc_move_assign = std::move(tc_copy);
	tc_copy_assign = std::move(tc_copy_assign);
	// TimerClass tc_error{ "" };
}
