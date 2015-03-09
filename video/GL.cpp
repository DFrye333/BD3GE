#include "GL.h"

/*
 * 	GL class
 */

GL::GL()
{
	// Set the clear color of the screen.
	Vector3 cornflowerBlue(0.39f, 0.58f, 0.93f);
	glClearColor(cornflowerBlue.u.c.r, cornflowerBlue.u.c.g, cornflowerBlue.u.c.b, 1.0f);

	// Enable depth testing.
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	// Enable back-face culling.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Set the window shape.
	reshape(BD3GE_WINDOW_WIDTH, BD3GE_WINDOW_HEIGHT);

	glFlush();
}

void GL::reshape(GLsizei width, GLsizei height)
{
	if (width > 0 && width < BD3GE_SCREEN_WIDTH && height > 0 && height < BD3GE_SCREEN_HEIGHT)
	{
		mViewportWidth = width;
		mViewportHeight = height;
		glViewport(0, 0, mViewportWidth, mViewportHeight);
	}
}

const GLubyte* GL::getOpenGLVersion(void)
{
	return glGetString(GL_VERSION);
}

unsigned int GL::getViewportWidth(void)
{
	return mViewportWidth;
}

unsigned int GL::getViewportHeight(void)
{
	return mViewportHeight;
}
