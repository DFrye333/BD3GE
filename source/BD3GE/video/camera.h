#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "../management/component_manager.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../utility/matrix.h"
#include "../utility/object.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	extern "C" class BD3GE_API Camera : public Object {
		public:

								Camera(Transform world_transform);
								Camera();
								~Camera();
			Transform			get_view_transform() const;
			const Matrix4		get_view_projection_matrix();
			void				set_viewport(const unsigned int viewport_width, const unsigned int viewport_height);

		private:

			const Matrix4		get_projection_matrix();

			unsigned int viewport_width;
			unsigned int viewport_height;
			Matrix4 projection_transform;
			bool should_recalculate_projection_transform = true;
	};
}

#endif // CAMERA_H