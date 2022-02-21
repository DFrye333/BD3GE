#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <cstdlib>
#include <deque>
#include <utility>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glew/GL/glew.h>

// TODO: Can I eliminate this dependency on input.h?
#include "../input/input.h"
#include "../utility/color.h"
#include "../video/brush.h"
#include "../video/camera.h"
#include "../video/mesh.h"
#include "../video/renderable.h"
#include "../video/vertex.h"


#include <cmath>


namespace BD3GE {
	class Scene {
		public:
			Scene(const std::string models_directory);
			~Scene();
			Renderable* add_renderable(Renderable* object);
			void tick(Input* input);
			void mouse_move(Input* input);
			void render(void);
			Camera* get_camera(void);

		private:

			std::vector<Renderable*> renderables;
			std::vector<Light*> lights;
			std::vector<Material*> lit_materials;
			Camera* camera;
			Renderable* player;
			Renderable* scary_duck;
			std::vector<Renderable*> little_ducks;
			Renderable* light_renderable;
	};
}

#endif // BD3GE_SCENE_H
