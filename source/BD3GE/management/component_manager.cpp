#include "component_manager.h"

namespace BD3GE {
	Slotmap<Transform> ComponentManager::transforms;
	Slotmap<Renderable> ComponentManager::renderables;

	SlotmapKey ComponentManager::add_transform(Transform transform) {
		return transforms.insert(transform);
	}

	SlotmapKey ComponentManager::add_renderable(Renderable renderable) {
		return renderables.insert(renderable);
	}

	Transform* ComponentManager::get_transform(SlotmapKey transform_key) {
		return transforms.get(transform_key);
	}

	Renderable* ComponentManager::get_renderable(SlotmapKey renderable_key) {
		return renderables.get(renderable_key);
	}

	void ComponentManager::clear_all() {
		transforms.clear();
		renderables.clear();
	}
}