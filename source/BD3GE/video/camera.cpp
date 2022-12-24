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

	Vector3 Camera::to_world_space(Vector4 camera_space_vector) {
		return Vector3(get_world_transform()->get_matrix() * camera_space_vector);
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

	Region Camera::calculate_bounding_image_plane_projection_region() {
		return calculate_bounding_image_plane_projection_region(0.0f);
	}

	Region Camera::calculate_bounding_image_plane_projection_region(float plane_y) {
		float horizontal_fov = get_horizontal_fov_radians();
		float vertical_fov = get_vertical_fov_radians();

		Transform* world_transform = get_world_transform();
		Matrix4 world_transform_matrix = world_transform->get_matrix();
		Transform view_transform = get_view_transform();
		Matrix4 view_transform_matrix = view_transform.get_matrix();

		Vector3 camera_world_position = this->get_position();
		Vector3 camera_space_forward = Vector3(0, 0, -1);

		Transform camera_space_frustum_center(Vector3(0, 0, 0), camera_space_forward);
		Transform camera_space_frustum_left(Vector3(0, 0, 0), camera_space_forward);
		Transform camera_space_frustum_right(Vector3(0, 0, 0), camera_space_forward);
		Transform camera_space_frustum_bottom(Vector3(0, 0, 0), camera_space_forward);
		Transform camera_space_frustum_top(Vector3(0, 0, 0), camera_space_forward);

		camera_space_frustum_left.rotate(Vector3(0, horizontal_fov * 0.5f, 0));
		camera_space_frustum_right.rotate(Vector3(0, -horizontal_fov * 0.5f, 0));
		camera_space_frustum_bottom.rotate(Vector3(vertical_fov * 0.5f, 0, 0));
		camera_space_frustum_top.rotate(Vector3(-vertical_fov * 0.5f, 0, 0));

		// TODO: Use camera z-plane, rather than world y-plane, for more flexibility?
		Vector3 center_intersect = calculate_ray_plane_intercept(camera_world_position, ((*world_transform) * camera_space_frustum_center).get_forward(), plane_y);
		Vector3 left_intersect = calculate_ray_plane_intercept(camera_world_position, ((*world_transform) * camera_space_frustum_left).get_forward(), plane_y);
		Vector3 right_intersect = calculate_ray_plane_intercept(camera_world_position, ((*world_transform) * camera_space_frustum_right).get_forward(), plane_y);
		Vector3 bottom_intersect = calculate_ray_plane_intercept(camera_world_position, ((*world_transform) * camera_space_frustum_bottom).get_forward(), plane_y);
		Vector3 top_intersect = calculate_ray_plane_intercept(camera_world_position, ((*world_transform) * camera_space_frustum_top).get_forward(), plane_y);

		std::vector<Vector3> camera_framing_points = {
			view_transform_matrix * Vector4(left_intersect, 1.0f),
			view_transform_matrix * Vector4(right_intersect, 1.0f),
			view_transform_matrix * Vector4(bottom_intersect, 1.0f),
			view_transform_matrix * Vector4(top_intersect, 1.0f)
		};

		std::vector<Vector3> camera_corner_points = calculate_bounding_values(camera_framing_points, 0, 1);

		std::vector<Vector3> world_image_plane_projection_corner_points = {
			world_transform_matrix * Vector4(camera_corner_points[0], 1.0f),
			world_transform_matrix * Vector4(camera_corner_points[1], 1.0f),
			world_transform_matrix * Vector4(camera_corner_points[2], 1.0f),
			world_transform_matrix * Vector4(camera_corner_points[3], 1.0f)
		};

		std::vector<Vector3> world_bounding_region_corner_points = calculate_bounding_values(world_image_plane_projection_corner_points, 0, 2);

		return Region(
			Vector2(world_bounding_region_corner_points[0].v.g.x, world_bounding_region_corner_points[0].v.g.y),
			Vector2(
				world_bounding_region_corner_points[1].v.g.x - world_bounding_region_corner_points[0].v.g.x,
				world_bounding_region_corner_points[2].v.g.y - world_bounding_region_corner_points[0].v.g.y
			)
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
		if (direction.v.g.y != 0.0f) {
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
		} else if (origin.v.g.y == plane_y) {
			return Vector3(origin.v.g.x, plane_y, origin.v.g.z);
		} else { // If camera has zero pitch (numerator == 0) and pos.y != plane_y, the camera is not looking at y == plane_y, and therefore there is no solution.
			return Vector3();
		}
	}

	std::vector<Vector3> Camera::calculate_bounding_values(std::vector<Vector3> points, unsigned short dimension_0, unsigned short dimension_1) {
		float min_x = std::numeric_limits<float>::max();
		float max_x = std::numeric_limits<float>::min();
		float min_y = std::numeric_limits<float>::max();
		float max_y = std::numeric_limits<float>::min();

		for (Vector3 point : points) {
			min_x = point.v.a[dimension_0] < min_x ? point.v.a[dimension_0] : min_x;
			max_x = point.v.a[dimension_0] > max_x ? point.v.a[dimension_0] : max_x;
			min_y = point.v.a[dimension_1] < min_y ? point.v.a[dimension_1] : min_y;
			max_y = point.v.a[dimension_1] > max_y ? point.v.a[dimension_1] : max_y;
		}

		Vector3 bottom_left = Vector3(min_x, min_y, 0.0f);
		Vector3 bottom_right = Vector3(max_x, min_y, 0.0f);
		Vector3 top_left = Vector3(min_x, max_y, 0.0f);
		Vector3 top_right = Vector3(max_x, max_y, 0.0f);

		return std::vector<Vector3>{ bottom_left, bottom_right, top_left, top_right };
	}
}