#include "timer.h"

/*
 * 	Timer class
 */

/* 	Method: Timer constructor
 * 	Parameter: name - Descriptive name for the timer.
 * 	Parameter: delta - The time delta between timer due times.
 */
Timer::Timer(std::string name, double delta)
{
	mName = new std::string(name);
	mDelta = delta;
}

Timer::~Timer()
{
	if (mName)
	{
		delete mName;
		mName = NULL;
	}
}

void Timer::start(void)
{
	gettimeofday(&mStartTime, NULL);
}

bool Timer::isDue(void)
{
	double elapsedTime = 0.0;

	return isDue(&elapsedTime);
}

bool Timer::isDue(double* elapsedTime)
{
	*elapsedTime = 0.0;

	// Calculate the amount of time since the last due time.
	gettimeofday(&mLastTime, NULL);
	*elapsedTime = ((mLastTime.tv_sec - mStartTime.tv_sec) * 1000.0) + ((mLastTime.tv_usec - mStartTime.tv_usec) / 1000.0);

	// The timer is due.
	if (*elapsedTime >= mDelta)
	{
		// Reset the timer.
		gettimeofday(&mStartTime, NULL);
		return true;
	}

	// The timer is not due.
	else
	{
		return false;
	}
}
