#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

#include "../system/api.h"
#include "../utility/color.h"
#include "../video/brush.h"
#include "../video/camera.h"
#include "../video/mesh.h"
#include "../video/model.h"
#include "../video/renderable.h"
#include "../video/renderable_object.h"
#include "../video/shader.h"

namespace BD3GE {
	extern "C" class BD3GE_API Scene {
		public:
			Scene();
			~Scene();
			RenderableObject* add_renderable_object(RenderableObject* renderable_object);

			Camera* camera;
			std::vector<RenderableObject*> renderable_objects;
			std::vector<Light*> lights;
			std::vector<Material*> lit_materials;
	};
}

#endif // BD3GE_SCENE_H