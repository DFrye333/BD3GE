#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <limits>

#include "../management/component_manager.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../utility/log.h"
#include "../utility/matrix.h"
#include "../utility/object.h"
#include "../utility/region.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	extern "C" class BD3GE_API Camera : public Object {
		public:

									Camera(Transform world_transform);
									Camera();
									~Camera();
			float					get_horizontal_fov_degrees();
			float					get_horizontal_fov_radians();
			void					set_horizontal_fov_degrees(float horizontal_fov_degrees);
			void					set_horizontal_fov_radians(float horizontal_fov_radians);
			float					get_vertical_fov_degrees();
			float					get_vertical_fov_radians();
			Transform				get_view_transform() const;
			const Matrix4			get_view_projection_matrix();
			void					set_viewport(const unsigned int viewport_width, const unsigned int viewport_height);
			Region					calculate_bounding_image_plane_projection_region();
			Region					calculate_bounding_image_plane_projection_region(float plane_y); // TODO: Generalize this as a frustum volume?
			void					print_stats();

		private:

			Vector3					calculate_ray_plane_intercept(Vector3 origin, Vector3 direction, float plane_y);
			std::vector<Vector3>	calculate_bounding_values(std::vector<Vector3> points, unsigned short dimension_0, unsigned short dimension_1);
			const Matrix4			get_projection_matrix();

			unsigned int viewport_width;
			unsigned int viewport_height;
			float horizontal_fov;
			Matrix4 projection_transform;
			bool should_recalculate_projection_transform = true;
	};
}

#endif // CAMERA_H