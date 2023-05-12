#ifndef BD3GE_CUBEMAP_H
#define BD3GE_CUBEMAP_H

#include <string>

#include "../system/api.h"
#include "../system/globals.h"
#include "../management/shader_manager.h"
#include "../management/texture_manager.h"
#include "../video/brush.h"
#include "../video/material.h"
#include "../video/renderable.h"

namespace BD3GE {
	class BD3GE_API Cubemap : public Renderable {
		public:
			Cubemap(std::string cubemap_directory_path);
	};
}

#endif // BD3GE_CUBEMAP_H