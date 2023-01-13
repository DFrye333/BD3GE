#ifndef BD3GE_MODEL_MANAGER_H
#define BD3GE_MODEL_MANAGER_H

#include <map>
#include <string>

#include "../management/config_manager.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../video/model.h"

namespace BD3GE {
	extern "C" class BD3GE_API ModelManager {
		public:
			static const size_t load_model(std::string relative_file_path);
			static Model* get_model(std::string relative_file_path);
			static Model* get_model(const size_t texture_hash);

		private:
			static const size_t get_hash(std::string input);
			static const size_t get_model_hash(std::string relative_file_path);

			static std::hash<std::string> string_hasher;
			static std::map<const size_t, Model*> models;
	};
}

#endif // BD3GE_MODEL_MANAGER_H