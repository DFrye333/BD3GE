#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <GL/glew.h>

#include "../audio/ogg.h"
#include "../system/constants.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/renderable.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position, const Vector3 velocity);
							Object(const Vector3 position, const Vector3 velocity, Renderable* renderable);
			virtual			~Object();
			void			move();
			void			translate(Vector3 translation);
			void			scale(Vector3 scaler);
			void			rotate(Vector3 angle);
			virtual void	render(Transform viewProjectionTransform);
			void			set_position(Vector3 position) { this->worldTransform.translate(position); }
			Vector3			get_position()			{ return this->worldTransform.get_position(); }
			void			set_velocity(Vector3 velocity) { this->velocity = velocity; }

		protected:

			Transform worldTransform;
			Vector3 velocity;
			Ogg* ogg;	// TODO: Encapsulate OGG-specific stuff inside a class (i.e. "Audio" object).
			Renderable* renderable;
	};
}

#endif // BD3GE_OBJECT_H