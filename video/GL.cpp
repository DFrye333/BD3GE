#include "GL.h"

namespace BD3GE
{
	/*
	 * 	GL class
	 */

	GL::GL()
	{
		// Set the clear color of the screen.
		Vector3 cornflower_blue(0.39f, 0.58f, 0.93f);
		glClearColor(cornflower_blue.v.c.r, cornflower_blue.v.c.g, cornflower_blue.v.c.b, 1.0f);

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
		reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

		glFlush();
	}

	void GL::reshape(GLsizei width, GLsizei height)
	{
		if (width > 0 && width < SCREEN_WIDTH && height > 0 && height < SCREEN_HEIGHT)
		{
			m_viewport_width = width;
			m_viewport_height = height;
			glViewport(0, 0, m_viewport_width, m_viewport_height);
		}
	}

	const GLubyte* GL::get_openGL_version(void)
	{
		return glGetString(GL_VERSION);
	}

	unsigned int GL::get_viewport_width(void)
	{
		return m_viewport_width;
	}

	unsigned int GL::get_viewport_height(void)
	{
		return m_viewport_height;
	}
}