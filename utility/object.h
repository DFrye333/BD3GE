#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <GL/glew.h>

#include "../audio/ogg.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/matrix.h"
#include "../utility/vector.h"
#include "../video/shader.h"

class Object
{
	public:

		virtual			~Object() {};
		virtual void	render(void) {};
		void			setPosX(double x)	{ mPos.u.g.x = x; }
		void			setPosY(double y)	{ mPos.u.g.y = y; }
		void			setPosZ(double z)	{ mPos.u.g.z = z; }
		double			getPosX(void)		{ return mPos.u.g.x; }
		double			getPosY(void)		{ return mPos.u.g.y; }
		double			getPosZ(void)		{ return mPos.u.g.z; }
		Vector3			getColor(void)		{ return mColor; }
		void			move(void);
		void			setVelX(double x);
		void			setVelY(double y);
		void			setVelZ(double z);
		double			getVelX(void)	{ return mVel.u.g.x; }
		double			getVelY(void)	{ return mVel.u.g.y; }
		double			getVelZ(void)	{ return mVel.u.g.z; }
		double			getVelVec(void);
		void			addVelX(double x);
		void			addVelY(double y);
		void			addVelZ(double z);

	protected:

		Vector3		mPos;
		Vector3		mColor;
		Vector3		mVel;
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
						~Cube();
		virtual void	render(void);
		void			setSize(double size)	{ mSize = size; }
		double			getSize(void)			{ return mSize; }

	protected:

		double			mSize;
};

#endif // OBJECT_H
