#ifndef BD3GE_RENDERER_H
#define BD3GE_RENDERER_H

#include <set>

#include "../management/component_manager.h"
#include "../management/model_manager.h"
#include "../management/shader_manager.h"
#include "../management/texture_manager.h"
#include "../game/scene.h"
#include "../utility/log.h"
#include "../video/GL.h"

namespace BD3GE {
	class Renderer {
		public:
			Renderer();
			void load_scene(Scene* scene);
			void render();
			void reshape_viewport(unsigned int width, unsigned int height);
			void toggle_wireframe_mode();
		private:
			void cache_resources();
			void setup_renderable(Renderable* renderable);

			Scene* scene;
			GL gl;
			std::set<size_t> shader_ids;
	};
}

#endif // BD3GE_RENDERER_H