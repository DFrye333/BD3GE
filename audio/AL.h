#ifndef AL_H
#define AL_H

#include <cstddef>

#include "AL/al.h"
#include "AL/alc.h"

class AL
{
	public:

		void init(void);
		void quit(void);

	private:

		ALCdevice* device;
		ALCcontext* context;
};

#endif // AL_H
