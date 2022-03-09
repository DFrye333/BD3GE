#include "scene.h"

namespace BD3GE {
	Scene::Scene() {}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;
	}

	RenderableObject* Scene::add_renderable_object(RenderableObject* renderable_object) {
		renderable_objects.push_back(renderable_object);
		return renderable_object;
	}
}