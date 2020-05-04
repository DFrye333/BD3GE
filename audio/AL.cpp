#include "AL.h"

namespace BD3GE {
	/*
	 *	AL class
	 */
	AL::AL() {
		m_device = alcOpenDevice(NULL);
		m_context = alcCreateContext(m_device, NULL);
		alcMakeContextCurrent(m_context);
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	}

	AL::~AL() {
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}
}