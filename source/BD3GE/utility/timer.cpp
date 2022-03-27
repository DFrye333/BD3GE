#include "timer.h"

namespace BD3GE {
	Timer::Timer(std::string name, uint64_t timer_frequency_Hz) : name(name), timer_frequency_Hz(timer_frequency_Hz), is_running(false), system_frequency_Hz(1), start_stamp(0), lap_stamp(0), total_pause_duration(0), fresh_pause_duration(0) {}
}