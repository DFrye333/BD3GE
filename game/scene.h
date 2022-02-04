#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <deque>
#include <utility>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>

// TODO: Can I eliminate this dependency on input.h?
#include "../input/input.h"
#include "../utility/color.h"
#include "../utility/object.h"
#include "../video/brush.h"
#include "../video/camera.h"
#include "../video/mesh.h"


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
			Camera* getCamera(void);

		private:

			std::vector<Renderable*> renderables;
			Camera* camera;
			Object* player;
			Object* scaryDuck;
			Object* light;
	};
}

#endif // BD3GE_SCENE_H
