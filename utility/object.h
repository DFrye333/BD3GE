#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <glew/GL/glew.h>

#include "../system/constants.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position);
			virtual			~Object();
			void			set_position(Vector3 position);
			void			set_scale(Vector3 scaler);
			void			set_orientation(Vector3 orientation);
			void			translate(Vector3 translation);
			void			rotate(Vector3 angle);
			Vector3			get_position();

		protected:

			Transform world_transform;
	};
}

#endif // BD3GE_OBJECT_H