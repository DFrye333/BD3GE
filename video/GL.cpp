#include "GL.h"

namespace BD3GE {
	/*
	 * 	GL class
	 */

	GL::GL() {
		// Set the clear color of the screen.
		Vector3 dark(0.25f, 0.25f, 0.25f);
		glClearColor(dark.v.c.r, dark.v.c.g, dark.v.c.b, 1.0f);

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

		// Enable alpha blending.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Set the window shape.
		reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

		glFlush();
	}

	void GL::reshape(GLsizei width, GLsizei height) {
		if (width > 0 && width < SCREEN_WIDTH && height > 0 && height < SCREEN_HEIGHT) {
			viewportWidth = width;
			viewportHeight = height;
			glViewport(0, 0, viewportWidth, viewportHeight);
		}
	}

	const void GL::print_info(void) {
		g_log.write(
			BD3GE::LOG_TYPE::INFO,
			"Vendor: " + std::string((char*)get_vendor()) + "\n" +
			"Renderer: " + std::string((char*)get_renderer()) + "\n" +
			"Version: " + std::string((char*)get_version()) + "\n" +
			"Shading Language Version: " + std::string((char*)get_shading_language_version())
		);
	}

	const GLubyte* GL::get_vendor(void) {
		return glGetString(GL_VENDOR);
	}

	const GLubyte* GL::get_renderer(void) {
		return glGetString(GL_RENDERER);
	}

	const GLubyte* GL::get_version(void) {
		return glGetString(GL_VERSION);
	}

	const GLubyte* GL::get_shading_language_version(void) {
		return glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	unsigned int GL::get_viewport_width(void) {
		return viewportWidth;
	}

	unsigned int GL::get_viewport_height(void) {
		return viewportHeight;
	}
}