#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

// TODO: Can I eliminate this dependency on input.h?
#include "../input/input.h"
#include "../management/model_manager.h"
#include "../management/shader_manager.h"
#include "../management/texture_manager.h"
#include "../utility/color.h"
#include "../video/brush.h"
#include "../video/camera.h"
#include "../video/mesh.h"
#include "../video/model.h"
#include "../video/renderable.h"
#include "../video/renderable_object.h"
#include "../video/shader.h"

namespace BD3GE {
	class Scene {
		public:
			Scene();
			~Scene();
			RenderableObject* add_renderable_object(RenderableObject* renderable_object);
			void tick(Input* input);
			void mouse_move(Input* input);

			Camera* camera;
			std::vector<RenderableObject*> renderable_objects;
			std::vector<Light*> lights;
			std::vector<Material*> lit_materials;
			RenderableObject* player;
			RenderableObject* scary_duck;
			RenderableObject* light_renderable;
			RenderableObject* earth;
			RenderableObject* backpack;
			std::vector<RenderableObject*> little_ducks;
	};
}

#endif // BD3GE_SCENE_H