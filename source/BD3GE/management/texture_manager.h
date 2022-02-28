#ifndef BD3GE_TEXTURE_MANAGER_H
#define BD3GE_TEXTURE_MANAGER_H

#include <map>
#include <string>

#include <glew/GL/glew.h>

#include "../system/constants.h"
#include "../video/texture.h"

namespace BD3GE {
	class TextureManager {
		public:
			static const size_t load_texture(std::string relative_file_path);
			static Texture* get_texture(std::string relative_file_path);
			static Texture* get_texture(const size_t texture_hash);

		private:
			static const size_t get_hash(std::string input);
			static const size_t get_texture_hash(std::string relative_file_path);

			static std::hash<std::string> string_hasher;
			static std::map<const size_t, Texture*> textures;
	};
}

#endif // BD3GE_TEXTURE_MANAGER_H