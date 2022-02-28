#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "../system/constants.h"
#include "../utility/matrix.h"
#include "../utility/object.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Camera : public Object {
		public:

								Camera(Vector3 position);
								Camera();
								~Camera();
			const Transform		get_projection_transform(void);
			const Transform		get_view_transform(void) const;
			const Transform		get_view_projection_transform(void);
			void				set_viewport(const unsigned int viewport_width, const unsigned int viewport_height);

		private:

			unsigned int viewport_width;
			unsigned int viewport_height;
			Transform projection_transform;
			bool should_recalculate_projection_transform = true;
	};
}

#endif // CAMERA_H