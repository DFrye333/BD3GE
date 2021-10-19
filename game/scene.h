#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <deque>
#include <utility>
#include <vector>

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


#include <cmath>


namespace BD3GE {
	class Scene {
		public:
			Scene(const std::string modelsDirectory);
			~Scene();
			Scene(std::vector<Object*> objects);
			Object* add_object(Object* object);
			Object* add_light(Object* light);
			void tick(Input* input);
			void mouse_drag(Input* input);
			void render(void);
			Camera* getCamera(void);

		private:

			Shader* lightingShader;
			std::vector<Object*> objects;
			std::vector<Object*> lights;
			Camera* camera;
			Object* player;
			Object* scaryDuck;
			Object* light;
	};
}

#endif // BD3GE_SCENE_H
