#ifndef BD3GE_FACTORY_H
#define BD3GE_FACTORY_H

#include <string>

#include "../os/win32.h"
#include "../utility/timer.h"

namespace BD3GE {
	class Factory {
		public:
			static Timer* createTimer(std::string name);
			static Timer* createTimer(std::string name, uint64_t timer_frequency_Hz);
	};
}

#endif // BD3GE_FACTORY_H