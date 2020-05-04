#include "timer.h"

namespace BD3GE
{
	/*
	 * 	Timer class
	 */

	/* 	Method: Timer constructor
	 * 	Parameter: name - Descriptive name for the timer.
	 * 	Parameter: timer_frequency_Hz - The time timer_frequency_Hz between timer due times.
	 */
	Timer::Timer(std::string name, uint64_t timer_frequency_Hz) {
		this->name = name;
		this->timer_frequency_Hz = timer_frequency_Hz;
	}

	Timer::~Timer() {}

	void Timer::start(void) {
#ifdef __linux__
#elif _WIN32
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		system_frequency_Hz = frequency.QuadPart;

		LARGE_INTEGER current_count;
		QueryPerformanceCounter(&current_count);

		start_stamp = (current_count.QuadPart * 1000) / system_frequency_Hz;
#endif
	}

	bool Timer::is_due() {
		bool is_due = false;

#ifdef __linux__
		// Calculate the amount of time since the last due time.
		gettimeofday(&m_time_last, NULL);
		*elapsed_time = ((m_time_last.tv_sec - m_time_start.tv_sec) * 1000.0f) + ((m_time_last.tv_usec - m_time_start.tv_usec) / 1000.0f);

		// The timer is due.
		if (*elapsed_time >= m_delta)
		{
			// Reset the timer.
			gettimeofday(&m_time_start, NULL);
			return true;
		}

		// The timer is not due.
		else
		{
			return false;
		}

#elif _WIN32
		LARGE_INTEGER current_count;
		QueryPerformanceCounter(&current_count);
		uint64_t current_stamp = (current_count.QuadPart * 1000) / system_frequency_Hz;

		if ((current_stamp - start_stamp) >= ((1.0f/ timer_frequency_Hz) * 1000)) {
			start_stamp = current_stamp;
			is_due = true;
		}

		return is_due;
#endif
	}
}