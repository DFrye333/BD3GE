#include "object.h"

namespace BD3GE {
	Object::Object() {}

	Object::Object(const Vector3 position) {
		set_position(position);
	}

	void Object::set_position(Vector3 position) {
		world_transform.set_position(position);
	}

	void Object::set_scale(Vector3 scaler) {
		world_transform.set_scale(scaler);
	}

	void Object::set_orientation(Vector3 orientation) {
		world_transform.set_orientation(orientation);
	}

	void Object::translate(Vector3 translation) {
		world_transform.translate(translation);
	}

	void Object::rotate(Vector3 rotation) {
		world_transform.rotate(rotation);
	}

	Vector3 Object::get_position() {
		return world_transform.get_position();
	}

	Transform& Object::get_transform() {
		return world_transform;
	}
}