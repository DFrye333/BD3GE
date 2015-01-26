#include "AL.h"

void AL::init(void)
{
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
}

void AL::quit(void)
{
	alcDestroyContext(context);
	alcCloseDevice(device);
}
