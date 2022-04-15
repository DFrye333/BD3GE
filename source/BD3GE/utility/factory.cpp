#include "factory.h"

namespace BD3GE {
	Timer* Factory::createTimer(std::string name) {
		return createTimer(name, 0);
	}

	Timer* Factory::createTimer(std::string name, uint64_t timer_frequency_Hz) {
#ifdef __linux__
#elif _WIN32
		if (timer_frequency_Hz > 0) {
			return new WinAPITimer(name, timer_frequency_Hz);
		} else {
			return new WinAPITimer(name);
		}
#endif
	}
}