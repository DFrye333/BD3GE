#ifndef BD3GE_RENDERER_H
#define BD3GE_RENDERER_H

#include <map>
#include <set>

#include <glew/GL/glew.h>

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
			void initialize_texture(size_t texture_id);
			void enable_texture(size_t texture_id, unsigned int index);
			void reshape_viewport(unsigned int width, unsigned int height);
			void toggle_wireframe_mode();
		private:
			void cache_resources();

			Scene* scene;
			GL gl;
			std::map<const size_t, unsigned int> texture_id_to_handle;
			std::set<size_t> shader_ids;
	};
}

#endif // BD3GE_RENDERER_H