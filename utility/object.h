#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include <string>

#include <assimp/mesh.h>
#include <GL/glew.h>

#include "../audio/ogg.h"
#include "../system/constants.h"
#include "../utility/matrix.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/mesh.h"
#include "../video/shader.h"

namespace BD3GE {
	class Object {
		public:

							Object();
							Object(const Vector3 position, const Vector3 color, const Vector3 velocity, const aiMesh* mesh);
			virtual			~Object();
			void			setup();
			void			move();
			void			scale(float scaler);
			void			rotate(Vector3 angle);
			virtual void	render(Transform view_projection_transform);
			void			set_position_X(float x)		{ m_position.v.g.x = x; }
			void			set_position_Y(float y)		{ m_position.v.g.y = y; }
			void			set_position_Z(float z)		{ m_position.v.g.z = z; }
			float			get_position_X()		{ return m_position.v.g.x; }
			float			get_position_Y()		{ return m_position.v.g.y; }
			float			get_position_Z()		{ return m_position.v.g.z; }
			Vector3&		get_color()				{ return m_color; }
			void			set_velocity_X(float x);
			void			set_velocity_Y(float y);
			void			set_velocity_Z(float z);
			void			set_velocity(float x, float y, float z);
			void			set_velocity(Vector3 velocity);
			float			get_velocity_X()		{ return m_velocity.v.g.x; }
			float			get_velocity_Y()		{ return m_velocity.v.g.y; }
			float			get_velocity_Z()		{ return m_velocity.v.g.z; }
			void			add_velocity_X(float x);
			void			add_velocity_Y(float y);
			void			add_velocity_Z(float z);

		protected:

			Transform	m_world_transform;
			Vector3		m_position;
			Vector3		m_color;
			Vector3		m_velocity;
			float		m_angle;
			Mesh*		mesh;
			Ogg*		m_OGG;	// TODO: Encapsulate OGG-specific stuff inside a class (i.e. "Audio" object).
			GLuint		vao;
			GLuint		vboPosition;
			GLuint		iboPosition;
			Shader*		shader;
	};
}

#endif // BD3GE_OBJECT_H
