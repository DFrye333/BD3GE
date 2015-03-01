#ifndef TIMER_H
#define TIMER_H

#include <string>

#include <sys/time.h>

class Timer
{
	public:

		Timer(std::string name, double interval);
		~Timer();
		void start(void);
		bool isDue(void);
		bool isDue(double* elapsedTime);

	private:

		std::string*		mName;
		double				mDelta;
		timeval				mStartTime;
		timeval				mLastTime;
};

#endif // TIMER_H
