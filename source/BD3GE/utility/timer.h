#ifndef BD3GE_TIMER_H
#define BD3GE_TIMER_H

#include <string>

namespace BD3GE {
	class Timer {
		public:

			Timer(std::string name, uint64_t timer_frequency_Hz);
			virtual ~Timer() {}
			virtual void start() = 0;
			virtual void pause() = 0;
			virtual void unpause() = 0;
			virtual void toggle_pause() = 0;
			virtual uint64_t elapsed() = 0;
			virtual bool is_due() = 0;

		protected:

			std::string			name;
			bool				is_running;
			uint64_t			timer_frequency_Hz;
			uint64_t			system_frequency_Hz;
			uint64_t			start_stamp;
			uint64_t			lap_stamp;
			uint64_t			total_pause_duration;
			uint64_t			fresh_pause_duration;
	};
}

#endif // BD3GE_TIMER_H