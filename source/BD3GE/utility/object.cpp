#include "object.h"

namespace BD3GE {
	Object::Object() {
		set_world_transform(Transform());
	}

	Object::Object(const Object& other) {
		*this = other;
	}

	Object::Object(Object&& other) {
		*this = std::move(other);
	}

	Object::~Object() {
		cleanup();
	}

	Transform* Object::get_world_transform() const {
		return ComponentManager::get_transform(this->world_transform);
	}

	Renderable* Object::get_renderable() const {
		return ComponentManager::get_renderable(this->renderable);
	}

	SlotmapKey Object::get_world_transform_key() const {
		return this->world_transform;
	}

	SlotmapKey Object::get_renderable_key() const {
		return this->renderable;
	}

	void Object::set_world_transform(Transform&& world_transform) {
		cleanup_transform();
		owns_transform = true;
		this->world_transform = ComponentManager::add_transform(std::move(world_transform));
	}

	void Object::set_renderable(Renderable&& renderable) {
		cleanup_renderable();
		owns_renderable = true;
		this->renderable = ComponentManager::add_renderable(std::move(renderable));
	}

	void Object::set_world_transform(SlotmapKey world_transform_key) {
		cleanup_transform();
		owns_transform = false;
		this->world_transform = world_transform_key;
	}

	void Object::set_renderable(SlotmapKey renderable_key) {
		cleanup_renderable();
		owns_renderable = false;
		this->renderable = renderable_key;
	}

	void Object::set_world_position(const Vector3 position) {
		get_world_transform()->set_position(position);
	}

	void Object::set_world_orientation(const Vector3 orientation) {
		get_world_transform()->set_orientation(orientation);
	}

	void Object::set_world_scale(Vector3 scaler) {
		get_world_transform()->set_scale(scaler);
	}

	void Object::world_translate(Vector3 translation) {
		get_world_transform()->translate(translation);
	}

	void Object::world_rotate(Vector3 rotation) {
		get_world_transform()->rotate(rotation);
	}

	void Object::local_translate(Vector3 translation) {
		Transform* world_transform = get_world_transform();
		Vector3 world_translation = world_transform->get_matrix() * Vector4(translation, 0.0f);
		world_transform->translate(world_translation);
	}

	void Object::local_rotate(Vector3 rotation) {
		Transform* world_transform = get_world_transform();
		Quaternion q = world_transform->get_orientation();
		Quaternion r = Quaternion(rotation);
		Quaternion world_rotation = q * r * q.inverse();
		world_transform->rotate(world_rotation);
	}

	Vector3 Object::get_position() {
		return get_world_transform()->get_position();
	}

	Vector3 Object::get_forward() {
		return get_world_transform()->get_forward();
	}

	Vector3 Object::get_left() {
		return get_world_transform()->get_left();
	}

	Vector3 Object::get_up() {
		return get_world_transform()->get_up();
	}
	
	const Object& Object::operator=(const Object& other) {
		this->owns_transform = other.owns_transform;
		if (owns_transform) {
			Transform* world_transform = other.get_world_transform();
			if (world_transform != nullptr) {
				this->world_transform = ComponentManager::add_transform(std::move(*world_transform));
			}
		}
		else {
			this->world_transform = other.world_transform;
		}

		this->owns_renderable = other.owns_renderable;
		if (owns_renderable) {
			Renderable* renderable = other.get_renderable();
			if (renderable != nullptr) {
				this->renderable = ComponentManager::add_renderable(std::move(*renderable));
			}
		}
		else {
			this->renderable = other.renderable;
		}

		return *this;
	}

	const Object& Object::operator=(Object&& other) {
		cleanup();

		this->owns_transform = other.owns_transform;
		this->owns_renderable = other.owns_renderable;
		this->world_transform = other.world_transform;
		this->renderable = other.renderable;

		other.owns_transform = false;
		other.owns_renderable = false;

		return *this;
	}

	void Object::cleanup() {
		cleanup_transform();
		cleanup_renderable();
	}

	void Object::cleanup_transform() {
		if (owns_transform) {
			ComponentManager::remove_transform(this->world_transform);
		}
	}

	void Object::cleanup_renderable() {
		if (owns_renderable) {
			ComponentManager::remove_renderable(this->renderable);
		}
	}
}