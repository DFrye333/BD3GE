#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <GL/glew.h>

#include "../system/constants.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position);
			virtual			~Object();
			void			translate(Vector3 translation);
			void			scale(Vector3 scaler);
			void			rotate(Vector3 angle);
			void			set_position(Vector3 position) { this->world_transform.translate(position); }
			Vector3			get_position()			{ return this->world_transform.get_position(); }

		protected:

			Transform world_transform;
	};
}

#endif // BD3GE_OBJECT_H