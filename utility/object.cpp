#include "object.h"

namespace BD3GE {
	/*
	 *	Object class
	 */

	Object::Object() {}

	Object::Object(const Vector3 position, const Vector3 color, const Vector3 velocity, const aiMesh* mesh) {
		// Initialize position attributes.
		m_position.v.g.x = position.v.g.x;
		m_position.v.g.y = position.v.g.y;
		m_position.v.g.z = position.v.g.z;

		// Initialize color attributes.
		m_color.v.c.r = color.v.c.r;
		m_color.v.c.g = color.v.c.g;
		m_color.v.c.b = color.v.c.b;

		// Initialize velocity attributes.
		m_velocity.v.g.x = velocity.v.g.x;
		m_velocity.v.g.y = velocity.v.g.y;
		m_velocity.v.g.z = velocity.v.g.z;

		m_angle = 0.0;

		m_world_transform.translate(m_position);

		m_mesh = new Mesh(mesh);

		// TODO: Revisit audio stuff later!
		// std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/audio/DH.ogg");
		// m_OGG = new Ogg(fileName);
		// m_OGG->play();
	}

	Object::~Object() {
		delete m_mesh;
		m_mesh = NULL;
	}

	void Object::move(void) {
		m_position.v.g.x += m_velocity.v.g.x;
		m_position.v.g.y += m_velocity.v.g.y;
		m_position.v.g.z += m_velocity.v.g.z;

		m_world_transform.translate(m_position);
	}

	void Object::scale(float scaler) {
		m_world_transform.scale(scaler);
	}

	void Object::rotate(Vector3 rotation) {
		m_world_transform.rotate(rotation);
	}

	void Object::render(Transform view_projection_transform) {
		m_mesh->render(view_projection_transform * m_world_transform);
	}

	void Object::set_velocity_X(float x) {
		m_velocity.v.g.x = x;
	}

	void Object::set_velocity_Y(float y) {
		m_velocity.v.g.y = y;
	}

	void Object::set_velocity_Z(float z) {
		m_velocity.v.g.z = z;
	}

	void Object::set_velocity(float x, float y, float z) {
		set_velocity_X(x);
		set_velocity_Y(y);
		set_velocity_Z(z);
	}

	void Object::set_velocity(Vector3 velocity) {
		m_velocity = velocity;
	}

	void Object::add_velocity_X(float x) {
		if (PLAYER_SPEED >= m_velocity.v.g.x && -PLAYER_SPEED <= m_velocity.v.g.x) {
			m_velocity.v.g.x += x;
		}
	}

	void Object::add_velocity_Y(float y) {
		if (PLAYER_SPEED >= m_velocity.v.g.y && -PLAYER_SPEED <= m_velocity.v.g.y) {
			m_velocity.v.g.y += y;
		}
	}

	void Object::add_velocity_Z(float z) {
		m_velocity.v.g.z += z;
	}
}
