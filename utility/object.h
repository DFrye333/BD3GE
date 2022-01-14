#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <GL/glew.h>

#include "../system/constants.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/renderable.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position);
							Object(const Vector3 position, Renderable* renderable);
			virtual			~Object();
			void			translate(Vector3 translation);
			void			scale(Vector3 scaler);
			void			rotate(Vector3 angle);
			virtual void	render(Transform viewProjectionTransform);
			void			set_position(Vector3 position) { this->worldTransform.translate(position); }
			Vector3			get_position()			{ return this->worldTransform.get_position(); }

		protected:

			Transform worldTransform;
			Renderable* renderable;
	};
}

#endif // BD3GE_OBJECT_H