#ifndef BD3GE_TEXTURE_H
#define BD3GE_TEXTURE_H

#include <string>

#include <GL/glew.h>

#include "../libraries/stb/stb_image.h"

#include "../system/globals.h"

namespace BD3GE {
	class Texture {
		public:
			Texture(std::string textureFilePath);
			Texture(int textureId, std::string textureFilePath);
			~Texture();

			unsigned char* data;
			int width;
			int height;
			int quantity_channels;
			int desired_quantity_channels;
			GLuint tboHandle;
			int textureId = GL_TEXTURE0;
	};
}

#endif // BD3GE_TEXTURE_H