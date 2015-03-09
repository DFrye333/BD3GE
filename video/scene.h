#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <GL/glew.h>

// TODO: Can I eliminate this dependency on input.h?
#include "../input/input.h"
#include "../utility/object.h"
#include "camera.h"

// Forward declaration.
class Object;

class Scene
{
	public:

				Scene();
				~Scene();
				Scene(std::vector<Object*> objects);
		void 	addObject(Object* object);
		void	tick(Input* input);
		void 	render(void);

	private:

		std::vector<Object*>	mObjects;
		Camera					mCamera;
};

#endif // SCENE_H
