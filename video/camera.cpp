#include "camera.h"

namespace BD3GE {
	/*
	 *	Camera Class
	 */

	Camera::Camera(Vector3 position) {
		m_viewport_width = WINDOW_WIDTH;
		m_viewport_height = WINDOW_HEIGHT;

		this->position.v.g.x = position.v.g.x;
		this->position.v.g.y = position.v.g.y;
		this->position.v.g.z = position.v.g.z;

		float frustum_scale = 1.0f;
		float z_near = 0.01f;
		float z_far = 1000.0f;

		m_projection_transform = Matrix4(
			frustum_scale / ((GLfloat)m_viewport_width / (GLfloat)m_viewport_height), 0, 0, 0,
			0.0f, frustum_scale, 0.0f, 0.0f,
			0.0f, 0.0f, ((z_near + z_far) / (z_near - z_far)), ((2 * z_near * z_far) / (z_near - z_far)),
			0.0f, 0.0f, -1.0f, 0.0f
		);

		worldTransform = Transform(Matrix4(
			1.0f, 0.0f, 0.0f, position.v.g.x,
			0.0f, 1.0f, 0.0f, position.v.g.y,
			0.0f, 0.0f, 1.0f, position.v.g.z,
			0.0f, 0.0f, 0.0f, 1.0f
		));
	}

	Camera::Camera() : Camera(Vector3(0, 0, 0)) {}

	Camera::~Camera() {}

	const Transform& Camera::get_projection_transform() const {
		return m_projection_transform;
	}

	const Transform Camera::get_view_transform() const {
		return this->worldTransform.inverse();
	}

	const Transform Camera::get_view_projection_transform() const {
		return this->get_projection_transform() * this->get_view_transform();
	}

	void Camera::set_viewport(const unsigned int viewport_width, const unsigned int viewport_height) {
		this->m_viewport_width = m_viewport_width;
		this->m_viewport_height = m_viewport_height;
	}
}