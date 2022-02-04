#include "object.h"

namespace BD3GE {
	Object::Object() {}

	Object::Object(const Vector3 position) {
		translate(position);

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// ogg = new Ogg(fileName);
		// ogg->play();
	}

	Object::~Object() {}

	void Object::translate(Vector3 translation) {
		worldTransform.translate(get_position() + translation);
	}

	void Object::scale(Vector3 scaler) {
		worldTransform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		worldTransform.rotate(rotation);
	}
}