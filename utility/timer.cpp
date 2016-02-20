#include "timer.h"

namespace BD3GE
{
	/*
	 * 	Timer class
	 */

	/* 	Method: Timer constructor
	 * 	Parameter: name - Descriptive name for the timer.
	 * 	Parameter: delta - The time delta between timer due times.
	 */
	Timer::Timer(std::string name, float delta)
	{
		m_name = new std::string(name);
		m_delta = delta;
	}

	Timer::~Timer()
	{
		delete m_name;
		m_name = NULL;
	}

	void Timer::start(void)
	{
		gettimeofday(&m_time_start, NULL);
	}

	bool Timer::is_due(void)
	{
		float elapsed_time = 0.0f;

		return is_due(&elapsed_time);
	}

	bool Timer::is_due(float* elapsed_time)
	{
		*elapsed_time = 0.0f;

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
	}
}