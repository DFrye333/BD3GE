#include "object.h"

/*
 *		PhysicsObject class
 */

void Object::move(void)
{
	if((false == input.getKeyState('w') && false == input.getKeyState('s')) || (true == input.getKeyState('w') && true == input.getKeyState('s')))
	{
		setVelY(0);
	}
	else if(true == input.getKeyState('w'))
	{
		addVelY(BD3GE_PLAYER_SPEED);
	}
	else if(true == input.getKeyState('s'))
	{
		addVelY(-BD3GE_PLAYER_SPEED);
	}
	if((false == input.getKeyState('a') && false == input.getKeyState('d')) || (true == input.getKeyState('a') && true == input.getKeyState('d')))
	{
		setVelX(0);
	}
	else if(true == input.getKeyState('a'))
	{
		addVelX(-BD3GE_PLAYER_SPEED);
	}
	else if(true == input.getKeyState('d'))
	{
		addVelX(BD3GE_PLAYER_SPEED);
	}
	if((false == input.getKeyState('q') && false == input.getKeyState('e')) || (true == input.getKeyState('q') && true == input.getKeyState('e')))
	{
		setVelZ(0);
	}
	else if(true == input.getKeyState('q'))
	{
		addVelZ(-BD3GE_PLAYER_SPEED);
	}
	else if(true == input.getKeyState('e'))
	{
		addVelZ(BD3GE_PLAYER_SPEED);
	}

	mPos.u.g.x += mVel.u.g.x;
	mPos.u.g.y += mVel.u.g.y;
	mPos.u.g.z += mVel.u.g.z / 10;
}

void Object::setVelX(double x)
{
	if(x > -10 && x < 10)
	{
		mVel.u.g.x = x;
	}
}

void Object::setVelY(double y)
{
	if(y > -10 && y < 10)
	{
		mVel.u.g.y = y;
	}
}

void Object::setVelZ(double z)
{
	if(z > -10 && z < 10)
	{
		mVel.u.g.z = z;
	}
}

void Object::addVelX(double x)
{
	if(BD3GE_PLAYER_SPEED >= mVel.u.g.x && -BD3GE_PLAYER_SPEED <= mVel.u.g.x)
	{
		mVel.u.g.x += x;
	}
}

void Object::addVelY(double y)
{
	if(BD3GE_PLAYER_SPEED >= mVel.u.g.y && -BD3GE_PLAYER_SPEED <= mVel.u.g.y)
	{
		mVel.u.g.y += y;
	}
}

void Object::addVelZ(double z)
{
	mVel.u.g.z += z;
}

/*
 * 		POSquare class
 */

Cube::Cube(const Vector3 position, const Vector3 color, const Vector3 velocity, const double size)
{
	mPos.u.g.x = position.u.g.x;
	mPos.u.g.y = position.u.g.y;
	mPos.u.g.z = position.u.g.z;

	mColor.u.c.r = color.u.c.r;
	mColor.u.c.g = color.u.c.g;
	mColor.u.c.b = color.u.c.b;

	mVel.u.g.x = velocity.u.g.x;
	mVel.u.g.y = velocity.u.g.y;
	mVel.u.g.z = velocity.u.g.z;

	mSize = size;

	mShader = new Shader();

	std::string fileName = std::string("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/DH.ogg");
	mOgg = new Ogg(fileName);
//	mOgg->play();

	// Cube vertex positions.
	mVertexPositionBuffer = new GLfloat[32];

	mVertexPositionBuffer[0] = mPos.u.g.x + (mSize / 2);
	mVertexPositionBuffer[1] = mPos.u.g.y + (mSize / 2);
	mVertexPositionBuffer[2] = mPos.u.g.z + (mSize / 2);
	mVertexPositionBuffer[3] = 1.0f;

	mVertexPositionBuffer[4] = mPos.u.g.x + (mSize / 2);
	mVertexPositionBuffer[5] = mPos.u.g.y - (mSize / 2);
	mVertexPositionBuffer[6] = mPos.u.g.z + (mSize / 2);
	mVertexPositionBuffer[7] = 1.0f;

	mVertexPositionBuffer[8] = mPos.u.g.x - (mSize / 2);
	mVertexPositionBuffer[9] = mPos.u.g.y - (mSize / 2);
	mVertexPositionBuffer[10] = mPos.u.g.z + (mSize / 2);
	mVertexPositionBuffer[11] = 1.0f;

	mVertexPositionBuffer[12] = mPos.u.g.x - (mSize / 2);
	mVertexPositionBuffer[13] = mPos.u.g.y + (mSize / 2);
	mVertexPositionBuffer[14] = mPos.u.g.z + (mSize / 2);
	mVertexPositionBuffer[15] = 1.0f;

	mVertexPositionBuffer[16] = mPos.u.g.x + (mSize / 2);
	mVertexPositionBuffer[17] = mPos.u.g.y + (mSize / 2);
	mVertexPositionBuffer[18] = mPos.u.g.z - (mSize / 2);
	mVertexPositionBuffer[19] = 1.0f;

	mVertexPositionBuffer[20] = mPos.u.g.x + (mSize / 2);
	mVertexPositionBuffer[21] = mPos.u.g.y - (mSize / 2);
	mVertexPositionBuffer[22] = mPos.u.g.z - (mSize / 2);
	mVertexPositionBuffer[23] = 1.0f;

	mVertexPositionBuffer[24] = mPos.u.g.x - (mSize / 2);
	mVertexPositionBuffer[25] = mPos.u.g.y - (mSize / 2);
	mVertexPositionBuffer[26] = mPos.u.g.z - (mSize / 2);
	mVertexPositionBuffer[27] = 1.0f;

	mVertexPositionBuffer[28] = mPos.u.g.x - (mSize / 2);
	mVertexPositionBuffer[29] = mPos.u.g.y + (mSize / 2);
	mVertexPositionBuffer[30] = mPos.u.g.z - (mSize / 2);
	mVertexPositionBuffer[31] = 1.0f;

	// Cube vertex indices.
	mIndexPositionBuffer = new GLushort[36];

	mIndexPositionBuffer[0] = 0;
	mIndexPositionBuffer[1] = 1;
	mIndexPositionBuffer[2] = 2;
	mIndexPositionBuffer[3] = 0;
	mIndexPositionBuffer[4] = 2;
	mIndexPositionBuffer[5] = 3;

	mIndexPositionBuffer[6] = 4;
	mIndexPositionBuffer[7] = 0;
	mIndexPositionBuffer[8] = 3;
	mIndexPositionBuffer[9] = 4;
	mIndexPositionBuffer[10] = 3;
	mIndexPositionBuffer[11] = 7;

	mIndexPositionBuffer[12] = 5;
	mIndexPositionBuffer[13] = 4;
	mIndexPositionBuffer[14] = 7;
	mIndexPositionBuffer[15] = 5;
	mIndexPositionBuffer[16] = 7;
	mIndexPositionBuffer[17] = 6;

	mIndexPositionBuffer[18] = 1;
	mIndexPositionBuffer[19] = 5;
	mIndexPositionBuffer[20] = 6;
	mIndexPositionBuffer[21] = 1;
	mIndexPositionBuffer[22] = 6;
	mIndexPositionBuffer[23] = 2;

	mIndexPositionBuffer[24] = 4;
	mIndexPositionBuffer[25] = 5;
	mIndexPositionBuffer[26] = 1;
	mIndexPositionBuffer[27] = 4;
	mIndexPositionBuffer[28] = 1;
	mIndexPositionBuffer[29] = 0;

	mIndexPositionBuffer[30] = 3;
	mIndexPositionBuffer[31] = 2;
	mIndexPositionBuffer[32] = 6;
	mIndexPositionBuffer[33] = 3;
	mIndexPositionBuffer[34] = 6;
	mIndexPositionBuffer[35] = 7;

	// Generate VAO.
	glGenVertexArrays(1, &mVAO);

	// Generate VBOs.
	glGenBuffers(1, &mVBO_Position);
	glGenBuffers(1, &mIBO_Position);

	// Setup for VAO.
	glBindVertexArray(mVAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO_Position);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), mVertexPositionBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_Position);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), mIndexPositionBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// Cleanup for VAO.
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Setup for shader's perspective matrix.
	glUseProgram(mShader->getProgramId());

	float frustrumScale = 1.0f;
	float zNear = 0.01f;
	float zFar = 1000.0f;

	Matrix4 perspectiveMatrix = Matrix4(
			frustrumScale / (gl.getViewportWidth() / (GLfloat)gl.getViewportHeight()), 0, 0, 0,
			0, frustrumScale, 0, 0,
			0, 0, ((zNear + zFar) / (zNear - zFar)), ((2 * zNear * zFar) / (zNear - zFar)),
			0, 0, -1.0f, 0
			);

	GLfloat perspectiveArray[16];
	perspectiveMatrix.toFloatArray(perspectiveArray);

	glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramId(), "perspectiveMatrix"), 1, GL_TRUE, perspectiveArray);

	glUseProgram(0);
}

Cube::~Cube()
{
	if (mVertexPositionBuffer)
	{
		delete[] mVertexPositionBuffer;
		mVertexPositionBuffer = NULL;
	}

	if (mIndexPositionBuffer)
	{
		delete[] mIndexPositionBuffer;
		mIndexPositionBuffer = NULL;
	}

	if (mShader)
	{
		delete mShader;
		mShader = NULL;
	}

	if (mOgg)
	{
		delete mOgg;
		mOgg = NULL;
	}
}

Cube::Cube(const Cube& source)
{
	mPos = source.mPos;
	mColor = source.mColor;
	mVBO_Position = source.mVBO_Position;
	mIBO_Position = source.mIBO_Position;
	mVertexPositionBuffer = source.mVertexPositionBuffer;
	mIndexPositionBuffer = source.mIndexPositionBuffer;
	mShader = source.mShader;
	mOgg = source.mOgg;
	mVel = source.mVel;
	mSize = source.mSize;
}

void Cube::render(void)
{
	// Setup for shader program.
	glUseProgram(mShader->getProgramId());

	// Update position.
	glUniform3f(glGetUniformLocation(mShader->getProgramId(), "offset"), mPos.u.g.x, mPos.u.g.y, mPos.u.g.z);
	glUniform4f(glGetUniformLocation(mShader->getProgramId(), "color"), mColor.u.c.r, mColor.u.c.g, mColor.u.c.b, 1.0f);

	// Draw cube using its VAO.
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	// Cleanup.
	glUseProgram(0);
}
