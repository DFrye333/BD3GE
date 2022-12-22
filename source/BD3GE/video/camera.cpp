#include "camera.h"

namespace BD3GE {
	Camera::Camera(Transform world_transform) : viewport_width(DEFAULT_WINDOW_WIDTH), viewport_height(DEFAULT_WINDOW_HEIGHT), horizontal_fov(135.0f * (BD3GE::PI / 180)) {
		this->world_transform = ComponentManager::add_transform(std::move(world_transform));
	}

	Camera::Camera() : Camera(Transform()) {}

	Camera::~Camera() {}

	float Camera::get_horizontal_fov_degrees() {
		return get_horizontal_fov_radians() * (180.0f / BD3GE::PI);
	}

	float Camera::get_horizontal_fov_radians() {
		return this->horizontal_fov;
	}

	void Camera::set_horizontal_fov_degrees(float horizontal_fov_degrees) {
		set_horizontal_fov_radians(horizontal_fov_degrees * (BD3GE::PI / 180.0f));
	}

	void Camera::set_horizontal_fov_radians(float horizontal_fov_radians) {
		this->horizontal_fov = horizontal_fov_radians;

		this->should_recalculate_projection_transform = true;
	}

	float Camera::get_vertical_fov_degrees() {
		return get_vertical_fov_radians() * (180.0f / BD3GE::PI);
	}

	float Camera::get_vertical_fov_radians() {
		return 2.0f * atan(tan(0.5f * get_horizontal_fov_radians()) / ((float)this->viewport_width / (float)this->viewport_height));
	}

	Transform Camera::get_view_transform() const {
		return ComponentManager::get_transform(this->world_transform)->inverse();
	}

	const Matrix4 Camera::get_view_projection_matrix() {
		return this->get_projection_matrix() * this->get_view_transform().get_matrix();
	}

	void Camera::set_viewport(const unsigned int viewport_width, const unsigned int viewport_height) {
		this->viewport_width = viewport_width;
		this->viewport_height = viewport_height;

		this->should_recalculate_projection_transform = true;
	}

	const Matrix4 Camera::get_projection_matrix() {
		if (should_recalculate_projection_transform) {
			float inverse_aspect_ratio = ((float)this->viewport_height / (float)this->viewport_width);
			float frustum_near = 1.0f;
			float frustum_far = 10000.0f;
			float frustum_right = tan(0.5f * get_horizontal_fov_radians()) * frustum_near;
			float frustum_left = -frustum_right;
			float frustum_top = frustum_right * inverse_aspect_ratio;
			float frustum_bottom = -frustum_top;
			float frustum_depth = frustum_far - frustum_near;
			float frustum_width = frustum_right - frustum_left;
			float frustum_height = frustum_top - frustum_bottom;

			this->projection_transform = Matrix4(
				(2.0f * frustum_near) / frustum_width, 0.0f, (frustum_right + frustum_left) / frustum_width, 0.0f,
				0.0f, (2.0f * frustum_near) / frustum_height, (frustum_top + frustum_bottom) / frustum_height, 0.0f,
				0.0f, 0.0f, -(frustum_far + frustum_near) / frustum_depth, (-2.0f * frustum_far * frustum_near) / frustum_depth,
				0.0f, 0.0f, -1.0f, 0.0f
			);

			this->should_recalculate_projection_transform = false;
		}
		return this->projection_transform;
	}
}