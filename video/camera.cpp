#include "camera.h"

namespace BD3GE {
	Camera::Camera(Vector3 position) : Object(position, Vector3(0, 0, 0)) {
		viewport_width = WINDOW_WIDTH;
		viewport_height = WINDOW_HEIGHT;
	}

	Camera::Camera() : Camera(Vector3(0, 0, 0)) {}

	Camera::~Camera() {}

	const Transform& Camera::get_projection_transform() const {
		float frustum_scale = 1.0f;
		float z_near = 0.01f;
		float z_far = 1000.0f;

		return Matrix4(
			frustum_scale / ((GLfloat)viewport_width / (GLfloat)viewport_height), 0, 0, 0,
			0.0f, frustum_scale, 0.0f, 0.0f,
			0.0f, 0.0f, ((z_near + z_far) / (z_near - z_far)), ((2 * z_near * z_far) / (z_near - z_far)),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

	const Transform Camera::get_view_transform() const {
		return this->worldTransform.inverse();
	}

	const Transform Camera::get_view_projection_transform() const {
		return this->get_projection_transform() * this->get_view_transform();
	}

	void Camera::set_viewport(const unsigned int viewport_width, const unsigned int viewport_height) {
		this->viewport_width = viewport_width;
		this->viewport_height = viewport_height;
	}
}