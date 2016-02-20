#ifndef AL_H
#define AL_H

#include <cstddef>

#include "AL/al.h"
#include "AL/alc.h"

namespace BD3GE
{
	class AL
	{
		public:

			AL();
			~AL();

		private:

			ALCdevice* m_device;
			ALCcontext* m_context;
	};
}

#endif // AL_H
