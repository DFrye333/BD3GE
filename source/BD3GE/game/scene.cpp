#include "scene.h"

namespace BD3GE {
	SceneNode::SceneNode() {}

	SceneNode::SceneNode(SlotmapKey parent, Object object) : parent(parent), object(object) {}

	SceneNode::SceneNode(const SceneNode& other) {
		*this = other;
	}

	const SceneNode& SceneNode::operator=(const SceneNode& other) {
		this->parent = other.parent;
		this->object = other.object;

		return *this;
	}

	Scene::Scene() : camera(nullptr) {
		root_scene_node = scene_nodes.insert(SceneNode(SlotmapKey(), Object()));
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;
	}

	SlotmapKey Scene::add_object(Object new_object) {
		return add_object(new_object, SlotmapKey());
	}

	SlotmapKey Scene::add_object(Object new_object, SlotmapKey parent_node) {
		SceneNode new_node = SceneNode(parent_node, new_object);

		if (!parent_node.is_initialized()) {
			new_node.parent = root_scene_node;
		}
		return scene_nodes.insert(new_node);
	}

	SlotmapKey Scene::add_renderable_object(Object new_node) {
		return add_renderable_object(new_node, root_scene_node);
	}

	SlotmapKey Scene::add_renderable_object(Object new_node, SlotmapKey parent_node) {
		SlotmapKey new_node_key = add_object(new_node, parent_node);
		renderable_objects.push_back(new_node_key);
		return new_node_key;
	}

	Object* Scene::get_object(SlotmapKey node_key) {
		SceneNode* node = scene_nodes[node_key];
		return node != nullptr ? &(node->object) : nullptr;
	}

	void Scene::remove_object(SlotmapKey node_key) {
		scene_nodes.remove(node_key);
	}
}