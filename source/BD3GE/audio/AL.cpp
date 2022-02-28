#include "AL.h"

namespace BD3GE {
	/*
	 *	AL class
	 */
	AL::AL() {
		device = alcOpenDevice(NULL);
		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	}

	AL::~AL() {
		alcDestroyContext(context);
		alcCloseDevice(device);
	}
}