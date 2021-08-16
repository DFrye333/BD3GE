#ifndef BD3GE_TEXTURE_H
#define BD3GE_TEXTURE_H

#include <string>

#include "../libraries/stb/stb_image.h"

#include "../system/globals.h"

namespace BD3GE {
	class Texture {
		public:
			Texture(std::string textureFilePath);
			~Texture();

		//protected:
			unsigned char* data;
			int width;
			int height;
			int quantityChannels;
			int desiredQuantityChannels;
	};
}

#endif // BD3GE_TEXTURE_H