#include "component_manager.h"

namespace BD3GE {
	Slotmap<Transform> ComponentManager::transforms;
	Slotmap<Renderable> ComponentManager::renderables;
	Slotmap<DirectionalLight> ComponentManager::directional_lights;
	Slotmap<PointLight> ComponentManager::point_lights;
	Slotmap<SpotLight> ComponentManager::spot_lights;

	SlotmapKey ComponentManager::add_transform(Transform transform) {
		return transforms.insert(std::move(transform));
	}

	SlotmapKey ComponentManager::add_renderable(Renderable renderable) {
		return renderables.insert(std::move(renderable));
	}

	SlotmapKey ComponentManager::add_directional_light(DirectionalLight directional_light) {
		return directional_lights.insert(std::move(directional_light));
	}

	SlotmapKey ComponentManager::add_point_light(PointLight point_light) {
		return point_lights.insert(std::move(point_light));
	}

	SlotmapKey ComponentManager::add_spot_light(SpotLight spot_light) {
		return spot_lights.insert(std::move(spot_light));
	}

	Transform* ComponentManager::get_transform(SlotmapKey transform_key) {
		return transforms.get(transform_key);
	}

	Renderable* ComponentManager::get_renderable(SlotmapKey renderable_key) {
		return renderables.get(renderable_key);
	}

	DirectionalLight* ComponentManager::get_directional_light(SlotmapKey directional_light_key) {
		return directional_lights.get(directional_light_key);
	}

	PointLight* ComponentManager::get_point_light(SlotmapKey point_light_key) {
		return point_lights.get(point_light_key);
	}

	SpotLight* ComponentManager::get_spot_light(SlotmapKey spot_light_key) {
		return spot_lights.get(spot_light_key);
	}

	void ComponentManager::remove_transform(SlotmapKey transform_key) {
		transforms.remove(transform_key);
	}

	void ComponentManager::remove_renderable(SlotmapKey renderable_key) {
		renderables.remove(renderable_key);
	}

	void ComponentManager::remove_directional_light(SlotmapKey directional_light_key) {
		directional_lights.remove(directional_light_key);
	}

	void ComponentManager::remove_point_light(SlotmapKey point_light_key) {
		point_lights.remove(point_light_key);
	}

	void ComponentManager::remove_spot_light(SlotmapKey spot_light_key) {
		spot_lights.remove(spot_light_key);
	}

	void ComponentManager::clear_all() {
		transforms.clear();
		renderables.clear();
		directional_lights.clear();
		point_lights.clear();
		spot_lights.clear();
	}
}