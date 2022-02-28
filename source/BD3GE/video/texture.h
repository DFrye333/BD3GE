#ifndef BD3GE_TEXTURE_H
#define BD3GE_TEXTURE_H

#include <cstdlib>
#include <string>

#include <stb/stb_image.h>

#include "../system/globals.h"
#include "../utility/log.h"

namespace BD3GE {
	class Texture {
		public:
			Texture();
			Texture(std::string texture_file_path);
			Texture(Texture& other);
			~Texture();
			Texture& operator=(Texture& other);
			size_t get_data_size();

			unsigned char* data;
			int width;
			int height;
			int quantity_channels;
			int desired_quantity_channels;
	};
}

#endif // BD3GE_TEXTURE_H