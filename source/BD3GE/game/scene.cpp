#include "scene.h"

namespace BD3GE {
	SceneNode::SceneNode() {}

	SceneNode::SceneNode(SlotmapKey parent, Object&& object) : parent(parent), object(std::move(object)) {}

	SceneNode::SceneNode(const SceneNode& other) {
		*this = other;
	}

	SceneNode::SceneNode(SceneNode&& other) {
		*this = std::move(other);
	}

	const SceneNode& SceneNode::operator=(const SceneNode& other) {
		this->parent = other.parent;
		this->object = other.object;

		return *this;
	}

	const SceneNode& SceneNode::operator=(SceneNode&& other) {
		this->parent = other.parent;
		this->object = std::move(other.object);

		return *this;
	}

	Scene::Scene() : camera(nullptr) {
		root_scene_node = scene_nodes.insert(SceneNode(SlotmapKey(), Object()));
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;
	}

	SlotmapKey Scene::add_object(Object&& new_object) {
		return add_object(std::move(new_object), SlotmapKey());
	}

	SlotmapKey Scene::add_object(Object&& new_object, SlotmapKey parent_node) {
		SceneNode new_node = SceneNode(parent_node, std::move(new_object));

		if (!parent_node.is_initialized()) {
			new_node.parent = root_scene_node;
		}
		return scene_nodes.insert(std::move(new_node));
	}

	SlotmapKey Scene::add_renderable_object(Object&& new_node) {
		return add_renderable_object(std::move(new_node), root_scene_node);
	}

	SlotmapKey Scene::add_renderable_object(Object&& new_node, SlotmapKey parent_node) {
		Vector3 new_node_relative_position = new_node.get_position();
		SlotmapKey new_node_key = add_object(std::move(new_node), parent_node);

		Transform ancestry_transform_stack = build_node_ancestry_transform_stack(new_node_key);

		Vector3 new_node_world_partitioning_position = ancestry_transform_stack.get_matrix() * Vector4(new_node_relative_position, 1.0f);
		renderable_objects_collection.push_back(new_node_key);
		renderable_objects_partitioning.insert(QuadtreeData(new_node_key, Vector2(new_node_world_partitioning_position.v.g.x, new_node_world_partitioning_position.v.g.z)));
		return new_node_key;
	}

	SlotmapKey Scene::add_renderable(Renderable&& renderable) {
		SlotmapKey renderable_key = ComponentManager::add_renderable(std::move(renderable));
		this->renderable_keys.push_back(renderable_key);

		return renderable_key;
	}

	SlotmapKey Scene::add_directional_light(DirectionalLight&& directional_light) {
		SlotmapKey directional_light_key = ComponentManager::add_directional_light(directional_light);
		this->directional_light_keys.push_back(directional_light_key);

		return directional_light_key;
	}

	SlotmapKey Scene::add_point_light(PointLight&& point_light) {
		SlotmapKey point_light_key = ComponentManager::add_point_light(point_light);
		this->point_light_keys.push_back(point_light_key);

		return point_light_key;
	}

	SlotmapKey Scene::add_spot_light(SpotLight&& spot_light) {
		SlotmapKey spot_light_key = ComponentManager::add_spot_light(spot_light);
		this->spot_light_keys.push_back(spot_light_key);

		return spot_light_key;
	}

	SlotmapKey Scene::set_skybox(std::string skybox_path) {
		SlotmapKey skybox_key = ComponentManager::add_renderable(Cubemap(skybox_path));
		this->skybox_key = skybox_key;
		return skybox_key;
	}

	Object* Scene::get_object(SlotmapKey node_key) {
		SceneNode* node = scene_nodes[node_key];
		return node != nullptr ? &(node->object) : nullptr;
	}

	DirectionalLight* Scene::get_directional_light(SlotmapKey directional_light_key) {
		return ComponentManager::get_directional_light(directional_light_key);
	}

	PointLight* Scene::get_point_light(SlotmapKey point_light_key) {
		return ComponentManager::get_point_light(point_light_key);
	}

	SpotLight* Scene::get_spot_light(SlotmapKey spot_light_key) {
		return ComponentManager::get_spot_light(spot_light_key);
	}

	void Scene::remove_object(SlotmapKey node_key) {
		Transform ancestry_transform_stack = build_node_ancestry_transform_stack(node_key);

		Object* object = get_object(node_key);
		Vector3 world_partitioning_position = ancestry_transform_stack.get_matrix() * Vector4(object->get_position(), 1.0f);
		renderable_objects_partitioning.remove(QuadtreeData(node_key, Vector2(world_partitioning_position.v.g.x, world_partitioning_position.v.g.z)));

		scene_nodes.remove(node_key);
	}

	void Scene::move_object(SlotmapKey node_key, Vector3 translation) {
		Object* object = get_object(node_key);
		Vector3 old_world_position = object->get_position();
		Vector3 new_world_position = old_world_position + translation;
		object->set_world_position(new_world_position);
		renderable_objects_partitioning.remove(QuadtreeData(node_key, Vector2(old_world_position.v.g.x, old_world_position.v.g.z)));
		renderable_objects_partitioning.insert(QuadtreeData(node_key, Vector2(new_world_position.v.g.x, new_world_position.v.g.z)));
	}

	std::vector<SlotmapKey> Scene::get_visible_renderable_keys() {
		if (ConfigManager::get_config_value_bool("enable_camera_frustum_culling") && should_frustum_cull) {
			Region bounding_image_plane_projection_region = this->camera->calculate_bounding_image_plane_projection_region();

			// Overfitting projection region helps to mitigate overly-aggressive culling at the edges of the camera frustum.
			float overfit = 1000;
			bounding_image_plane_projection_region.position -= BD3GE::Vector2(overfit, overfit);
			bounding_image_plane_projection_region.range += BD3GE::Vector2(2 * overfit, 2 * overfit);

			return this->renderable_objects_partitioning.collect_overlapping_nodes(bounding_image_plane_projection_region);
		} else {
			return renderable_objects_collection;
		}
	}

	Transform Scene::build_node_ancestry_transform_stack(SlotmapKey node_key) {
		Transform ancestry_transform_stack;
		SlotmapKey current_ancestor_key = scene_nodes.get(node_key)->parent;
		while (current_ancestor_key != root_scene_node) {
			SceneNode* current_ancestor_node = scene_nodes.get(current_ancestor_key);
			ancestry_transform_stack = *(current_ancestor_node->object.get_world_transform()) * ancestry_transform_stack;
			current_ancestor_key = current_ancestor_node->parent;
		}
		ancestry_transform_stack = *(get_object(root_scene_node)->get_world_transform()) * ancestry_transform_stack;

		return ancestry_transform_stack;
	}
}