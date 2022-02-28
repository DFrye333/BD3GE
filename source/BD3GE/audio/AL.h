#ifndef BD3GE_AL_H
#define BD3GE_AL_H

#include <cstddef>

#include <openal/al.h>
#include <openal/alc.h>

namespace BD3GE {
	class AL {
		public:

			AL();
			~AL();

		private:

			ALCdevice* device;
			ALCcontext* context;
	};
}

#endif // BD3GE_AL_H
