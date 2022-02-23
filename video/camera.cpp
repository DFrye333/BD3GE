#include "camera.h"

namespace BD3GE {
	Camera::Camera(Vector3 position) : Object(position) {
		viewport_width = WINDOW_WIDTH;
		viewport_height = WINDOW_HEIGHT;
	}

	Camera::Camera() : Camera(Vector3(0, 0, 0)) {}

	Camera::~Camera() {}

	const Transform Camera::get_projection_transform() {
		if (should_recalculate_projection_transform) {
			float frustum_scale = 5.0f;
			float z_near = 0.01f;
			float z_far = 10000.0f;

			this->projection_transform = Transform(Matrix4(
				frustum_scale / ((GLfloat)viewport_width / (GLfloat)viewport_height), 0, 0, 0,
				0.0f, frustum_scale, 0.0f, 0.0f,
				0.0f, 0.0f, ((z_near + z_far) / (z_near - z_far)), ((2 * z_near * z_far) / (z_near - z_far)),
				0.0f, 0.0f, -1.0f, 0.0f
			));

			this->should_recalculate_projection_transform = false;
		}
		return this->projection_transform;
	}

	const Transform Camera::get_view_transform() const {
		return this->world_transform.inverse();
	}

	const Transform Camera::get_view_projection_transform() {
		return this->get_projection_transform() * this->get_view_transform();
	}

	void Camera::set_viewport(const unsigned int viewport_width, const unsigned int viewport_height) {
		this->viewport_width = viewport_width;
		this->viewport_height = viewport_height;
		this->should_recalculate_projection_transform = true;
	}
}