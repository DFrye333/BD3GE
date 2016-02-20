#ifndef TIMER_H
#define TIMER_H

#include <string>

#include <sys/time.h>

namespace BD3GE
{
	class Timer
	{
		public:

			Timer(std::string name, float interval);
			~Timer();
			void start(void);
			bool is_due(void);
			bool is_due(float* elapsed_time);

		private:

			std::string*		m_name;
			float				m_delta;
			timeval				m_time_start;
			timeval				m_time_last;
	};
}

#endif // TIMER_H
