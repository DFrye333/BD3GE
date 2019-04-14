#ifndef BD3GE_TIMER_H
#define BD3GE_TIMER_H

#include <ctime>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace BD3GE
{
	class Timer
	{
		public:

			Timer(std::string name, uint64_t timer_frequency_Hz);
			~Timer();
			void start(void);
			bool is_due(void);

		private:

			std::string			name;
			uint64_t			timer_frequency_Hz;
			uint64_t			system_frequency_Hz;
			uint64_t			start_stamp;
	};
}

#endif // BD3GE_TIMER_H
