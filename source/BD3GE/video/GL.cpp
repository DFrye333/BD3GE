#include "GL.h"

namespace BD3GE {
	GL::GL() : is_wireframe_mode_enabled(false) {
		// Set the clear color of the screen.
		Color dark(16, 16, 16);
		Color gray(64, 64, 64);
		glClearColor(dark.rgb.v.c.r, dark.rgb.v.c.g, dark.rgb.v.c.b, 1.0f);

		// Enable depth testing.
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		// Enable back-face culling.
		// TODO: This should not *always* be enabled, as some objects may need both faces rendered to display properly (e.g. two-sided textures).
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		// Enable alpha blending.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Set the window shape.
		reshape_viewport(WINDOW_WIDTH, WINDOW_HEIGHT);

		glFlush();
	}

	void GL::create_texture_handle(unsigned int* texture_handle) {
		glGenTextures(1, texture_handle);
	}

	void GL::clear_buffers() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GL::reshape_viewport(unsigned int width, unsigned int height) {
		if (width > 0 && width < SCREEN_WIDTH && height > 0 && height < SCREEN_HEIGHT) {
			viewport_width = width;
			viewport_height = height;
			glViewport(0, 0, (GLsizei)viewport_width, (GLsizei)viewport_height);
		}
	}

	const void GL::print_info(void) {
		g_log->write(
			Log::TYPE::INFO,
			std::string("OpenGL information:\n") +
			"\t\t\t\t\t\tVendor: " + std::string((char*)get_vendor()) + "\n" +
			"\t\t\t\t\t\tRenderer: " + std::string((char*)get_renderer()) + "\n" +
			"\t\t\t\t\t\tVersion: " + std::string((char*)get_version()) + "\n" +
			"\t\t\t\t\t\tShading Language Version: " + std::string((char*)get_shading_language_version())
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
		return viewport_width;
	}

	unsigned int GL::get_viewport_height(void) {
		return viewport_height;
	}

	void GL::set_wireframe_mode(bool should_enable_wireframe_mode) {
		glPolygonMode(GL_FRONT, should_enable_wireframe_mode ? GL_LINE : GL_FILL);
		glPolygonMode(GL_BACK, should_enable_wireframe_mode ? GL_LINE : GL_FILL);

		is_wireframe_mode_enabled = should_enable_wireframe_mode;
	}

	void GL::toggle_wireframe_mode() {
		is_wireframe_mode_enabled = !is_wireframe_mode_enabled;
		set_wireframe_mode(is_wireframe_mode_enabled);
	}
}