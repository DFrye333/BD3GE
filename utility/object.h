#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <GL/glew.h>

#include "../audio/ogg.h"
#include "../system/constants.h"
#include "../utility/color.h"
#include "../utility/matrix.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/mesh.h"
#include "../video/renderable.h"
#include "../video/shader.h"
#include "../video/texture.h"

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
			void			set_position(Vector3 position)	{ this->position = position; }
			void			set_position_X(float x)			{ position.v.g.x = x; }
			void			set_position_Y(float y)			{ position.v.g.y = y; }
			void			set_position_Z(float z)			{ position.v.g.z = z; }
			Vector3			get_position()			{ return position; }
			float			get_position_X()		{ return position.v.g.x; }
			float			get_position_Y()		{ return position.v.g.y; }
			float			get_position_Z()		{ return position.v.g.z; }
			void			set_velocity_X(float x);
			void			set_velocity_Y(float y);
			void			set_velocity_Z(float z);
			void			set_velocity(float x, float y, float z);
			void			set_velocity(Vector3 velocity);
			float			get_velocity_X()		{ return velocity.v.g.x; }
			float			get_velocity_Y()		{ return velocity.v.g.y; }
			float			get_velocity_Z()		{ return velocity.v.g.z; }
			void			add_velocity_X(float x);
			void			add_velocity_Y(float y);
			void			add_velocity_Z(float z);

		protected:

			Transform worldTransform;
			Vector3	position;
			Vector3 velocity;
			Ogg* ogg;	// TODO: Encapsulate OGG-specific stuff inside a class (i.e. "Audio" object).
			Renderable* renderable;
	};
}

#endif // BD3GE_OBJECT_H