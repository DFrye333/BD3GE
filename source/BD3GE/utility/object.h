#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include "../system/api.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	extern "C" class BD3GE_API Object {
		public:

							Object();
							Object(const Vector3 position);
			void			set_position(Vector3 position);
			void			set_scale(Vector3 scaler);
			void			set_orientation(Vector3 orientation);
			void			translate(Vector3 translation);
			void			rotate(Vector3 angle);
			Vector3			get_position();
			Transform&		get_transform();

		protected:

			Transform world_transform;
	};
}

#endif // BD3GE_OBJECT_H