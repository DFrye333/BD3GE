#include "object.h"

namespace BD3GE {
	Object::Object() : renderable(nullptr) {}

	Object::Object(const Vector3 position) : Object(position, nullptr) {}

	Object::Object(const Vector3 position, Renderable* renderable) : renderable(renderable) {
		translate(position);

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// ogg = new Ogg(fileName);
		// ogg->play();
	}

	Object::~Object() {
		delete renderable;
		renderable = nullptr;
	}

	void Object::translate(Vector3 translation) {
		worldTransform.translate(get_position() + translation);
	}

	void Object::scale(Vector3 scaler) {
		worldTransform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		worldTransform.rotate(rotation);
	}

	void Object::render(Transform viewProjectionTransform) {
		if (renderable != nullptr) {
			renderable->render(worldTransform, viewProjectionTransform);
		}
	}
}