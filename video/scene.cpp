#include "scene.h"

/*
 * 	Scene class
 */

Scene::Scene()
{
}

Scene::Scene(std::vector<Object*> objects)
{
	mObjects = objects;
}

Scene::~Scene()
{
}

void Scene::addObject(Object* object)
{
	mObjects.push_back(object);
}

void Scene::render(void)
{
	for (std::vector<Object*>::size_type i = 0; i != mObjects.size(); ++i)
	{
		mObjects[i]->render();
	}
}
