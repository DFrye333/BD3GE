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
#include "../video/shader.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position, const Color color, const Vector3 velocity, const Drawable* drawable);
			virtual			~Object();
			void			setup();
			void			move();
			void			scale(float scaler);
			void			rotate(Vector3 angle);
			virtual void	render(Transform view_projection_transform);
			void			set_position_X(float x)		{ position.v.g.x = x; }
			void			set_position_Y(float y)		{ position.v.g.y = y; }
			void			set_position_Z(float z)		{ position.v.g.z = z; }
			float			get_position_X()		{ return position.v.g.x; }
			float			get_position_Y()		{ return position.v.g.y; }
			float			get_position_Z()		{ return position.v.g.z; }
			Color&			get_color()				{ return color; }
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
			Vector3	 position;
			Color color;
			Vector3 velocity;
			float angle;
			const Drawable* drawable;
			Ogg* m_OGG;	// TODO: Encapsulate OGG-specific stuff inside a class (i.e. "Audio" object).
			GLuint vao;
			GLuint vboPosition;
			GLuint iboPosition;
			Shader* shader;
	};
}

#endif // BD3GE_OBJECT_H
