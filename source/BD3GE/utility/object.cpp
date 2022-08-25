#include "object.h"

namespace BD3GE {
	Object::Object() {
		set_world_transform(Transform());
	}

	Transform* Object::get_world_transform() {
		return ComponentManager::get_transform(this->world_transform);
	}

	Renderable* Object::get_renderable() {
		return ComponentManager::get_renderable(this->renderable);
	}

	void Object::set_world_transform(Transform world_transform) {
		this->world_transform = ComponentManager::add_transform(world_transform);
	}

	void Object::set_renderable(Renderable renderable) {
		this->renderable = ComponentManager::add_renderable(renderable);
	}

	void Object::set_position(const Vector3 position) {
		get_world_transform()->set_position(position);
	}

	void Object::set_orientation(const Vector3 orientation) {
		get_world_transform()->set_orientation(orientation);
	}

	void Object::set_scale(Vector3 scaler) {
		get_world_transform()->set_scale(scaler);
	}

	void Object::translate(Vector3 translation) {
		get_world_transform()->translate(translation);
	}

	void Object::rotate(Vector3 angle) {
		get_world_transform()->rotate(angle);
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
}