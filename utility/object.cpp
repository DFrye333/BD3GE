#include "object.h"

namespace BD3GE {
	Object::Object() {}

	Object::Object(const Vector3 position, const Vector3 velocity, Renderable* renderable) {
		this->position.v.g.x = position.v.g.x;
		this->position.v.g.y = position.v.g.y;
		this->position.v.g.z = position.v.g.z;

		this->velocity.v.g.x = velocity.v.g.x;
		this->velocity.v.g.y = velocity.v.g.y;
		this->velocity.v.g.z = velocity.v.g.z;

		worldTransform.translate(this->position);

		this->renderable = renderable;
		renderable->setup();

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// ogg = new Ogg(fileName);
		// ogg->play();

	}

	Object::~Object() {
		delete renderable;
		renderable = NULL;
	}

	void Object::move(void) {
		this->position.v.g.x += velocity.v.g.x;
		this->position.v.g.y += velocity.v.g.y;
		this->position.v.g.z += velocity.v.g.z;

		worldTransform.translate(position);
	}

	void Object::scale(float scaler) {
		worldTransform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		worldTransform.rotate(rotation);
	}

	void Object::render(Transform viewProjectionTransform) {
		renderable->render(viewProjectionTransform * worldTransform);
	}

	void Object::set_velocity_X(float x) {
		velocity.v.g.x = x;
	}

	void Object::set_velocity_Y(float y) {
		velocity.v.g.y = y;
	}

	void Object::set_velocity_Z(float z) {
		velocity.v.g.z = z;
	}

	void Object::set_velocity(float x, float y, float z) {
		set_velocity_X(x);
		set_velocity_Y(y);
		set_velocity_Z(z);
	}

	void Object::set_velocity(Vector3 velocity) {
		velocity = velocity;
	}

	void Object::add_velocity_X(float x) {
		if (PLAYER_SPEED >= velocity.v.g.x && -PLAYER_SPEED <= velocity.v.g.x) {
			velocity.v.g.x += x;
		}
	}

	void Object::add_velocity_Y(float y) {
		if (PLAYER_SPEED >= velocity.v.g.y && -PLAYER_SPEED <= velocity.v.g.y) {
			velocity.v.g.y += y;
		}
	}

	void Object::add_velocity_Z(float z) {
		velocity.v.g.z += z;
	}
}
