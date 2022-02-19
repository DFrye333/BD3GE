#ifndef BD3GE_TIMER_H
#define BD3GE_TIMER_H

#include <string>

namespace BD3GE {
	class Timer {
		public:

			virtual ~Timer() {}
			virtual void start(void) = 0;
			virtual bool is_due(void) = 0;

		private:

			std::string			name;
			bool				is_running;
			long long			timer_frequency_Hz;
			long long			system_frequency_Hz;
			long long			start_stamp;
	};
}

#endif // BD3GE_TIMER_H