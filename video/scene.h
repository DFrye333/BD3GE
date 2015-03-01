#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../utility/object.h"

// Forward declaration.
class Object;

class Scene
{
	public:

		Scene();
		~Scene();
		Scene(std::vector<Object*> objects);
		void addObject(Object* object);
		void render(void);

	private:

		std::vector<Object*>	mObjects;
};

#endif // SCENE_H
