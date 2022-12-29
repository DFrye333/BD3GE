#include "camera.h"

namespace BD3GE {
	Camera::Camera(Transform world_transform) : viewport_width(DEFAULT_WINDOW_WIDTH), viewport_height(DEFAULT_WINDOW_HEIGHT), horizontal_fov(ConfigManager::get_config_value_float("camera_fov_horizontal") * (BD3GE::PI / 180)) {
		this->world_transform = ComponentManager::add_transform(std::move(world_transform));

		calculate_view_frustum();
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

		calculate_view_frustum();

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

		calculate_view_frustum();

		this->should_recalculate_projection_transform = true;
	}

	Vector3 Camera::to_world_space(Vector4 camera_space_vector) {
		return Vector3(get_world_transform()->get_matrix() * camera_space_vector);
	}

	const Matrix4 Camera::get_projection_matrix() {
		if (should_recalculate_projection_transform) {
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

	void Camera::calculate_view_frustum() {
		this->aspect_ratio = ((float)this->viewport_width / (float)this->viewport_height);
		this->frustum_near = 1.0f;
		this->frustum_far = 10000.0f;
		this->frustum_right = tan(0.5f * get_horizontal_fov_radians()) * frustum_near;
		this->frustum_left = -frustum_right;
		this->frustum_top = frustum_right / aspect_ratio;
		this->frustum_bottom = -frustum_top;
		this->frustum_depth = frustum_far - frustum_near;
		this->frustum_width = frustum_right - frustum_left;
		this->frustum_height = frustum_top - frustum_bottom;
	}

	Region Camera::calculate_bounding_image_plane_projection_region() {
		return calculate_bounding_image_plane_projection_region(0.0f);
	}

	Region Camera::calculate_bounding_image_plane_projection_region(float plane_y) {
		Transform* world_transform = get_world_transform();
		Matrix4 world_transform_matrix = world_transform->get_matrix();
		Transform view_transform = get_view_transform();
		Matrix4 view_transform_matrix = view_transform.get_matrix();

		Vector3 camera_world_position = this->get_position();
		Vector3 camera_space_forward = Vector3(0, 0, -1);

		Vector3 bottom_left_screen = Vector3(this->frustum_left, this->frustum_bottom, 0);
		Vector3 bottom_right_screen = Vector3(this->frustum_right, this->frustum_bottom, 0);
		Vector3 top_left_screen = Vector3(this->frustum_left, this->frustum_top, 0);
		Vector3 top_right_screen = Vector3(this->frustum_right, this->frustum_top, 0);
		Vector3 bottom_left_frustum = camera_space_forward + bottom_left_screen;
		Vector3 bottom_right_frustum = camera_space_forward + bottom_right_screen;
		Vector3 top_left_frustum = camera_space_forward + top_left_screen;
		Vector3 top_right_frustum = camera_space_forward + top_right_screen;

		// TODO: Use camera z-plane, rather than world y-plane, for more flexibility?
		Vector3 bottom_left_intersect = calculate_ray_plane_intercept(camera_world_position, world_transform_matrix * Vector4(bottom_left_frustum, 0.0f), plane_y);
		Vector3 bottom_right_intersect = calculate_ray_plane_intercept(camera_world_position, world_transform_matrix * Vector4(bottom_right_frustum, 0.0f), plane_y);
		Vector3 top_left_intersect = calculate_ray_plane_intercept(camera_world_position, world_transform_matrix * Vector4(top_left_frustum, 0.0f), plane_y);
		Vector3 top_right_intersect = calculate_ray_plane_intercept(camera_world_position, world_transform_matrix * Vector4(top_right_frustum, 0.0f), plane_y);

		Vector3 bounding_bottom_left_world = bottom_left_intersect;
		Vector3 bounding_top_right_world = top_right_intersect;
		for (Vector3 intersect_world : std::vector<Vector3>{ bottom_right_intersect, top_left_intersect, top_right_intersect }) {
			bounding_bottom_left_world.v.g.x = intersect_world.v.g.x < bounding_bottom_left_world.v.g.x ? intersect_world.v.g.x : bounding_bottom_left_world.v.g.x;
			bounding_bottom_left_world.v.g.z = intersect_world.v.g.z < bounding_bottom_left_world.v.g.z ? intersect_world.v.g.z : bounding_bottom_left_world.v.g.z;
			bounding_top_right_world.v.g.x = intersect_world.v.g.x > bounding_top_right_world.v.g.x ? intersect_world.v.g.x : bounding_top_right_world.v.g.x;
			bounding_top_right_world.v.g.z = intersect_world.v.g.z > bounding_top_right_world.v.g.z ? intersect_world.v.g.z : bounding_top_right_world.v.g.z;
		}

		// TODO: Cache this result?
		return Region(
			Vector2(bounding_bottom_left_world.v.g.x, bounding_bottom_left_world.v.g.z),
			Vector2(bounding_top_right_world.v.g.x - bounding_bottom_left_world.v.g.x, bounding_top_right_world.v.g.z - bounding_bottom_left_world.v.g.z)
		);
	}

	void Camera::print_stats() {
		g_log->write(Log::TYPE::INFO, "Camera Stats");
		g_log->write(Log::TYPE::INFO, "==========");
		g_log->write(Log::TYPE::INFO, "Position: " + this->get_position().to_string());
		g_log->write(Log::TYPE::INFO, "Forward: " + this->get_forward().to_string());
		g_log->write(Log::TYPE::INFO, "Field of view (horizontal): " + std::to_string(get_horizontal_fov_degrees()));
		g_log->write(Log::TYPE::INFO, "Field of view (vertical): " + std::to_string(get_vertical_fov_degrees()));
		g_log->write(Log::TYPE::INFO, "==========");
	}

	Vector3 Camera::calculate_ray_plane_intercept(Vector3 origin, Vector3 direction, float plane_y) {
		if (direction.v.g.y != 0.0f) { // Ray intercepts y == plane_y.
			float m = 0.0f;
			float x = 0.0f;
			float z = 0.0f;
			if (direction.v.g.x == 0) {
				x = origin.v.g.x;
			} else {
				m = direction.v.g.y / direction.v.g.x;
				x = (plane_y + ((m * origin.v.g.x) - origin.v.g.y)) / m;
			}
			if (direction.v.g.z == 0) {
				z = origin.v.g.z;
			} else {
				m = direction.v.g.y / direction.v.g.z;
				z = (plane_y + ((m * origin.v.g.z) - origin.v.g.y)) / m;
			}

			return Vector3(x, plane_y, z);
		} else if (origin.v.g.y == plane_y) { // Camera is sitting on y == plane_y.
			return Vector3(origin.v.g.x, plane_y, origin.v.g.z);
		} else { // If camera has zero pitch (numerator == 0) and pos.y != plane_y, the camera is not looking at y == plane_y, and therefore there is no solution.
			return Vector3();
		}
	}
}