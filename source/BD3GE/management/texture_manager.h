#ifndef BD3GE_TEXTURE_MANAGER_H
#define BD3GE_TEXTURE_MANAGER_H

#include <map>
#include <string>

#include "../management/config_manager.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../video/texture.h"

namespace BD3GE {
	extern "C" class BD3GE_API TextureManager {
		public:
			static const size_t load_texture(std::string texture_relative_file_path);
			static const size_t load_cubemap(std::string cubemap_relative_file_path);
			static Texture* get_texture(std::string texture_relative_file_path);
			static Texture* get_texture(const size_t texture_hash);
			static std::vector<Texture*> get_cubemap(std::string cubemap_relative_file_path);
			static std::vector<Texture*> get_cubemap(const size_t cubemap_hash);

		private:
			static const size_t get_hash(std::string input);
			static const size_t get_path_hash(std::string relative_file_path);

			static std::hash<std::string> string_hasher;
			static std::map<const size_t, Texture*> textures;
			static std::map<const size_t, size_t[6]> cubemaps;
	};
}

#endif // BD3GE_TEXTURE_MANAGER_H