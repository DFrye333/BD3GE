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
		Vector2 position = Vector2(new_node.get_position().v.g.x, new_node.get_position().v.g.z);
		SlotmapKey new_node_key = add_object(std::move(new_node), parent_node);
		renderable_objects_collection.push_back(new_node_key);
		renderable_objects_partitioning.insert(QuadtreeData(new_node_key, position));
		return new_node_key;
	}

	SlotmapKey Scene::add_renderable(Renderable&& renderable) {
		SlotmapKey renderable_key = ComponentManager::add_renderable(std::move(renderable));
		this->renderable_keys.push_back(renderable_key);

		return renderable_key;
	}

	Object* Scene::get_object(SlotmapKey node_key) {
		SceneNode* node = scene_nodes[node_key];
		return node != nullptr ? &(node->object) : nullptr;
	}

	void Scene::remove_object(SlotmapKey node_key) {
		scene_nodes.remove(node_key);
	}

	std::vector<SlotmapKey> Scene::get_visible_renderable_keys() {
		if (this->should_frustum_cull) {
			Region bounding_image_plane_projection_region = this->camera->calculate_bounding_image_plane_projection_region();
			return this->renderable_objects_partitioning.collect_overlapping_nodes(bounding_image_plane_projection_region);
		} else {
			return renderable_objects_collection;
		}
	}
}