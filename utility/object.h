#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <GL/glew.h>

#include "../audio/ogg.h"
#include "../system/constants.h"
#include "../utility/matrix.h"
#include "../utility/vector.h"
#include "../video/shader.h"

class Object
{
	public:

		virtual			~Object() {};
		virtual void	render(void) {};
		void			setPositionX(double x)	{ mPosition.u.g.x = x; }
		void			setPositionY(double y)	{ mPosition.u.g.y = y; }
		void			setPositionZ(double z)	{ mPosition.u.g.z = z; }
		double			getPositionX(void)		{ return mPosition.u.g.x; }
		double			getPositionY(void)		{ return mPosition.u.g.y; }
		double			getPositionZ(void)		{ return mPosition.u.g.z; }
		Vector3			getColor(void)			{ return mColor; }
		void			move(void);
		void			setVelocityX(double x);
		void			setVelocityY(double y);
		void			setVelocityZ(double z);
		double			getVelocityX(void)		{ return mVelocity.u.g.x; }
		double			getVelocityY(void)		{ return mVelocity.u.g.y; }
		double			getVelocityZ(void)		{ return mVelocity.u.g.z; }
		double			getVelocityVector(void);
		void			addVelocityX(double x);
		void			addVelocityY(double y);
		void			addVelocityZ(double z);

	protected:

		Matrix4		mModelTransform;
		Vector3		mPosition;
		Vector3		mColor;
		Vector3		mVelocity;
		GLuint		mVBO_Position;
		GLuint		mIBO_Position;
		GLuint		mVAO;
		GLfloat*	mVertexPositionBuffer;
		GLushort*	mIndexPositionBuffer;
		Shader*		mShader;
		Ogg*		mOgg;	// TODO: Encapsulate OGG-specific stuff inside a class (i.e. "Audio" object).
};

class Cube : public Object
{
	public:

						Cube(const Vector3 position, const Vector3 color, const Vector3 velocity, const double size);
						Cube(const Cube& source);
		virtual			~Cube();
		virtual void	render(void);
		void			setSize(double size)	{ mSize = size; }
		double			getSize(void)			{ return mSize; }

	protected:

		double			mSize;
};

#endif // OBJECT_H
