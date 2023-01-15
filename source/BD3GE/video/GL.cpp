#include "GL.h"

namespace BD3GE {
	GL::GL() : vao_handles(nullptr), vbo_handles(nullptr), ibo_handles(nullptr), renderables_quantity(0), is_wireframe_mode_enabled(false) {
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
		reshape_viewport(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

		glFlush();
	}

	GL::~GL() {
		delete_buffers();
	}

	void GL::create_buffers(unsigned int buffers_quantity) {
		delete_buffers();

		this->buffers_quantity = buffers_quantity;
		this->renderables_quantity = 0;

		vao_handles = new GLuint[buffers_quantity];
		vbo_handles = new GLuint[buffers_quantity];
		ibo_handles = new GLuint[buffers_quantity];
		
		// Generates VAOs.
		glGenVertexArrays(buffers_quantity, vao_handles);

		// Generates VBOs.
		glGenBuffers(buffers_quantity, vbo_handles);
		glGenBuffers(buffers_quantity, ibo_handles);
	}

	void GL::delete_buffers() {
		if (buffers_quantity > 0) {
			glDeleteVertexArrays(buffers_quantity, vao_handles);
			delete[] vao_handles;
			vao_handles = nullptr;

			glDeleteBuffers(buffers_quantity, vbo_handles);
			delete[] vbo_handles;
			vbo_handles = nullptr;

			glDeleteBuffers(buffers_quantity, ibo_handles);
			delete[] ibo_handles;
			ibo_handles = nullptr;
		}
	}

	void GL::setup_vaos(std::vector<RenderableUnit*> renderable_units) {
		for (RenderableUnit* renderable_unit : renderable_units) {
			setup_vao(renderable_unit);
		}
	}

	void GL::setup_vao(RenderableUnit* renderable_unit) {
		renderable_unit->geometry.vao_handle = vao_handles[renderables_quantity];

		glBindVertexArray(renderable_unit->geometry.vao_handle);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_handles[renderables_quantity]);
		glBufferData(GL_ARRAY_BUFFER, renderable_unit->geometry.num_vertices * sizeof(Vertex), renderable_unit->geometry.vbo, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_handles[renderables_quantity]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderable_unit->geometry.num_indices * sizeof(GLuint), renderable_unit->geometry.ibo, GL_DYNAMIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(0);

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(1);

		// UVs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));
		glEnableVertexAttribArray(2);

		Material* material = renderable_unit->material;
		if (material->type == Material::TYPE::MAPPED) {
			MappedMaterial* mapped_material = (MappedMaterial*)material;
			initialize_texture(mapped_material->map_diffuse_id);
			initialize_texture(mapped_material->map_specular_id);
		}

		++renderables_quantity;
	}

	void GL::draw_renderable_unit(RenderableUnit* renderable_unit) {
		// Draw!
		glBindVertexArray(renderable_unit->geometry.vao_handle);
		glDrawElements(GL_TRIANGLES, renderable_unit->geometry.num_indices, GL_UNSIGNED_INT, 0);
	}

	void GL::create_texture_handle(unsigned int* texture_handle) {
		glGenTextures(1, texture_handle);
	}

	void GL::initialize_texture(size_t texture_id) {
		unsigned int texture_handle;
		if (!texture_id_to_handle.contains(texture_id)) {
			create_texture_handle(&texture_handle);
			texture_id_to_handle[texture_id] = texture_handle;
		}
		texture_handle = texture_id_to_handle[texture_id];

		glBindTexture(GL_TEXTURE_2D, texture_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Texture* texture = TextureManager::get_texture(texture_id);
		if (!texture) { return; }

		GLint format = 0;
		switch (texture->quantity_channels) {
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void GL::enable_texture(size_t texture_id, unsigned int index) {
		unsigned int texture_handle = texture_id_to_handle[texture_id];
		// TODO: Make this dynamic.
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texture_handle);
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