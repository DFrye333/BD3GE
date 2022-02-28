#include "renderer.h"

namespace BD3GE {
	Renderer::Renderer() : Renderer(nullptr) {}

	Renderer::Renderer(Scene* scene) : scene(scene) {
		g_log.write(Log::TYPE::INFO, "Renderer initializing...");
		gl.print_info();
		load_scene(scene);
	}

	void Renderer::load_scene(Scene* scene) {
		if (!scene) { return; }

		unsigned int renderable_units_count = 0;
		for (RenderableObject* renderable_object : scene->renderable_objects) {
			// Lazy-loads renderables.
			if (!renderable_object->renderable) {
				renderable_object->renderable = ModelManager::get_model(renderable_object->renderable_id);
			}
			Renderable* renderable = renderable_object->renderable;

			for (RenderableUnit* renderable_unit : renderable->renderable_units) {
				++renderable_units_count;
			}
		}
		GLuint* vao_handles = new GLuint[renderable_units_count];
		GLuint* vbo_handles = new GLuint[renderable_units_count];
		GLuint* ibo_handles = new GLuint[renderable_units_count];

		// Generates VAOs.
		glGenVertexArrays(renderable_units_count, vao_handles);

		// Generates VBOs.
		glGenBuffers(renderable_units_count, vbo_handles);
		glGenBuffers(renderable_units_count, ibo_handles);

		unsigned int current_renderable_unit_index = 0;
		for (RenderableObject* renderable_object : scene->renderable_objects) {
			for (RenderableUnit* renderable_unit : renderable_object->renderable->renderable_units) {
				renderable_unit->geometry.vao_handle = vao_handles[current_renderable_unit_index];

				// Setup for VAO.
				glBindVertexArray(renderable_unit->geometry.vao_handle);

				glBindBuffer(GL_ARRAY_BUFFER, vbo_handles[current_renderable_unit_index]);
				glBufferData(GL_ARRAY_BUFFER, renderable_unit->geometry.num_vertices * sizeof(Vertex), renderable_unit->geometry.vbo, GL_DYNAMIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_handles[current_renderable_unit_index]);
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

				++current_renderable_unit_index;
			}
		}

		cache_resources();
	}

	void Renderer::render() {
		if (!scene) { return; }

		gl.clear_buffers();

		Vector3 camera_position = scene->camera->get_position();
		for (Light* light : scene->lights) {
			for (size_t shader_id : shader_ids) {
				Shader* shader = ShaderManager::get_shader(shader_id);
				shader->set_light(light);
				shader->set_uniform("viewer_position", camera_position);
			}
		}

		Transform view_projection_transform = scene->camera->get_view_projection_transform();
		for (RenderableObject* renderable_object : scene->renderable_objects) {
			for (RenderableUnit* renderable_unit : renderable_object->renderable->renderable_units) {
				Shader* shader = ShaderManager::get_shader(renderable_unit->material->shader_id);

				shader->enable();

				// Stacks transforms hierarchically, from the current renderable unit all the way up to the world.
				Transform world_transform_stack = Transform();
				TransformNode* current_transform_node = renderable_unit->transform_node;
				while (current_transform_node) {
					world_transform_stack = current_transform_node->transform * world_transform_stack;
					current_transform_node = current_transform_node->parent;
				}
				world_transform_stack = renderable_object->get_transform() * world_transform_stack;

				shader->set_uniform("world_transform", world_transform_stack.get_matrix());
				shader->set_uniform("inverse_world_transform", world_transform_stack.get_matrix().inverse());
				shader->set_uniform("view_projection_transform", view_projection_transform.get_matrix());

				Material* material = renderable_unit->material;
				if (material->type == Material::TYPE::SIMPLE) {
					SimpleMaterial* simple_material = ((SimpleMaterial*)renderable_unit->material);

					shader->set_uniform("is_material_mapped", false);
					shader->set_uniform("simple_material.color_ambient", simple_material->color_ambient.rgb);
					shader->set_uniform("simple_material.color_diffuse", simple_material->color_diffuse.rgb);
					shader->set_uniform("simple_material.color_specular", simple_material->color_specular.rgb);
					shader->set_uniform("simple_material.gloss_factor", simple_material->gloss_factor);
				} else if (material->type == Material::TYPE::MAPPED) {
					MappedMaterial* mapped_material = ((MappedMaterial*)renderable_unit->material);

					shader->set_uniform("is_material_mapped", true);
					shader->set_uniform("mapped_material.map_diffuse[0]", 0);
					shader->set_uniform("mapped_material.map_specular[0]", 1);
					shader->set_uniform("mapped_material.gloss_factor", mapped_material->gloss_factor);

					enable_texture(mapped_material->map_diffuse_id, 0);
					enable_texture(mapped_material->map_specular_id, 1);
				}

				// Draw!
				glBindVertexArray(renderable_unit->geometry.vao_handle);
				glDrawElements(GL_TRIANGLES, renderable_unit->geometry.num_indices, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);

				shader->disable();
			}
		}
	}

	void Renderer::initialize_texture(size_t texture_id) {
		unsigned int texture_handle;
		if (!texture_id_to_handle.contains(texture_id)) {
			gl.create_texture_handle(&texture_handle);
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

	void Renderer::enable_texture(size_t texture_id, unsigned int index) {
		unsigned int texture_handle = texture_id_to_handle[texture_id];
		// TODO: Make this dynamic.
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texture_handle);
	}

	void Renderer::reshape_viewport(unsigned int width, unsigned int height) {
		gl.reshape_viewport(width, height);

		if (scene) {
			scene->camera->set_viewport(gl.get_viewport_width(), gl.get_viewport_height());
		}
	}

	void Renderer::toggle_wireframe_mode() {
		gl.toggle_wireframe_mode();
	}

	void Renderer::cache_resources() {
		shader_ids.clear();

		for (RenderableObject* renderable_object : scene->renderable_objects) {
			for (RenderableUnit* renderable_unit : renderable_object->renderable->renderable_units) {
				shader_ids.insert(renderable_unit->material->shader_id);
			}
		}
	}
}