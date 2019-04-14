#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <deque>
#include <vector>

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>

// TODO: Can I eliminate this dependency on input.h?
#include "../input/input.h"
#include "../utility/object.h"
#include "../video/camera.h"


#include <cmath>


namespace BD3GE
{
	class Scene
	{
		public:

							Scene(const std::string file_path);
							~Scene();
							Scene(std::vector<Object*> objects);
			void 			add_object(Object* object);
			void			tick(Input* input);
			void 			render(void);
			Camera& 	getCamera(void);

		private:

			std::vector<Object*>	m_objects;
			Camera				m_camera;
	};
}

#endif // BD3GE_SCENE_H
