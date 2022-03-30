#include "camera.h"

namespace BD3GE {
	Camera::Camera(Transform world_transform) : viewport_width(DEFAULT_WINDOW_WIDTH), viewport_height(DEFAULT_WINDOW_HEIGHT) {
		this->world_transform = ComponentManager::add_transform(world_transform);
	}

	Camera::Camera() : Camera(Transform()) {}

	Camera::~Camera() {}

	const Transform Camera::get_projection_transform() {
		if (should_recalculate_projection_transform) {
			float frustum_scale = 5.0f;
			float z_near = 1.0f;
			float z_far = 10000.0f;

			this->projection_transform = Transform(Matrix4(
				frustum_scale / ((float)viewport_width / (float)viewport_height), 0, 0, 0,
				0.0f, frustum_scale, 0.0f, 0.0f,
				0.0f, 0.0f, ((z_near + z_far) / (z_near - z_far)), ((2 * z_near * z_far) / (z_near - z_far)),
				0.0f, 0.0f, -1.0f, 0.0f
			));

			this->should_recalculate_projection_transform = false;
		}
		return this->projection_transform;
	}

	const Transform Camera::get_view_transform() const {
		return ComponentManager::get_transform(this->world_transform)->inverse();
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