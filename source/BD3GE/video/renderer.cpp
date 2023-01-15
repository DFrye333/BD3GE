#include "renderer.h"

namespace BD3GE {
	Renderer::Renderer() : scene(nullptr) {
		g_log->write(Log::TYPE::INFO, "Renderer initializing...");
		gl.print_info();
	}

	void Renderer::load_scene(Scene* scene) {
		if (!scene) { return; }

		this->scene = scene;
		this->scene->camera->set_viewport(gl.get_viewport_width(), gl.get_viewport_height());

		unsigned int renderable_units_count = 0;
		for (SlotmapKey scene_node_key : scene->renderable_objects_collection) {
			SceneNode* scene_node = scene->scene_nodes.get(scene_node_key);
			Object& scene_object = scene_node->object;
			Renderable* renderable = scene_object.get_renderable();

			// Lazy-loads renderables.
			if (renderable->renderable_units.empty()) {
				renderable = ModelManager::get_model(renderable->renderable_id);
				scene_object.set_renderable(ComponentManager::add_renderable(*renderable));
			}

			for (RenderableUnit* renderable_unit : renderable->renderable_units) {
				++renderable_units_count;
			}
		}
		renderable_units_count += scene->renderable_keys.size();
		
		gl.create_buffers(renderable_units_count);

		for (SlotmapKey scene_node_key : scene->renderable_objects_collection) {
			SceneNode* scene_node = scene->scene_nodes.get(scene_node_key);
			Object& scene_object = scene_node->object;
			Renderable* renderable = ComponentManager::get_renderable(scene_object.get_renderable_key());

			gl.setup_vaos(renderable->renderable_units);
		}
		for (SlotmapKey renderable_key : scene->renderable_keys) {
			Renderable* renderable = ComponentManager::get_renderable(renderable_key);
			gl.setup_vaos(renderable->renderable_units);
		}

		cache_resources();
	}

	void Renderer::render() {
		gl.clear_buffers();

		if (!scene || !scene->camera) { return; }

		float gamma = ConfigManager::get_config_value_float("gamma");
		bool enable_blinn_phong = ConfigManager::get_config_value_bool("enable_blinn_phong");

		Transform* camera_transform = scene->camera->get_world_transform();
		Vector3 camera_position = camera_transform->get_position();
		for (Light* light : scene->lights) {
			for (size_t shader_id : shader_ids) {
				Shader* shader = ShaderManager::get_shader(shader_id);
				shader->set_light(light);
				shader->set_uniform("viewer_position", camera_position);
			}
		}

		Matrix4 view_projection_transform = scene->camera->get_view_projection_matrix();
		for (SlotmapKey scene_node_key : scene->get_visible_renderable_keys()) {
			SceneNode* scene_node = scene->scene_nodes.get(scene_node_key);
			if (!scene_node) { continue; }

			// Stacks transforms up the scene hierarchy.
			Object& scene_object = scene_node->object;
			Transform scene_object_transform = *scene_object.get_world_transform();
			SceneNode* parent_node = scene->scene_nodes.get(scene_node->parent);
			Transform* parent_node_transform = parent_node != nullptr ? parent_node->object.get_world_transform() : nullptr;
			while (parent_node_transform != nullptr) {
				scene_object_transform = *parent_node_transform * scene_object_transform;
				parent_node = scene->scene_nodes.get(parent_node->parent);
				parent_node_transform = parent_node != nullptr ? parent_node->object.get_world_transform() : nullptr;
			}

			Renderable* renderable = ComponentManager::get_renderable(scene_object.get_renderable_key());
			for (RenderableUnit* renderable_unit : renderable->renderable_units) {
				// Stacks transforms up the renderable hierarchy.
				Transform world_transform_stack = Transform();
				TransformNode* current_transform_node = renderable_unit->transform_node;
				while (current_transform_node) {
					world_transform_stack = current_transform_node->transform * world_transform_stack;
					current_transform_node = current_transform_node->parent;
				}
				world_transform_stack = scene_object_transform * world_transform_stack;

				Shader* shader = ShaderManager::get_shader(renderable_unit->material->shader_id);
				shader->enable();

				shader->set_uniform("world_transform", world_transform_stack.get_matrix());
				shader->set_uniform("inverse_world_transform", world_transform_stack.get_matrix().inverse());
				shader->set_uniform("view_projection_transform", view_projection_transform);
				shader->set_uniform("gamma", gamma);
				shader->set_uniform("enable_blinn_phong", enable_blinn_phong);

				Material* material = renderable_unit->material;
				if (material->type == Material::TYPE::SIMPLE) {
					SimpleMaterial* simple_material = ((SimpleMaterial*)renderable_unit->material);

					shader->set_uniform("is_material_mapped", false);
					shader->set_uniform("simple_material.color_ambient", simple_material->color_ambient.rgb);
					shader->set_uniform("simple_material.color_diffuse", simple_material->color_diffuse.rgb);
					shader->set_uniform("simple_material.color_specular", simple_material->color_specular.rgb);
				} else if (material->type == Material::TYPE::MAPPED) {
					MappedMaterial* mapped_material = ((MappedMaterial*)renderable_unit->material);

					shader->set_uniform("is_material_mapped", true);
					shader->set_uniform("mapped_material.map_diffuse[0]", 0);
					shader->set_uniform("mapped_material.map_specular[0]", 1);

					gl.enable_texture(mapped_material->map_diffuse_id, 0);
					gl.enable_texture(mapped_material->map_specular_id, 1);
				}
				shader->set_uniform("material.gloss_factor", material->gloss_factor);
				shader->set_uniform("material.gamma_diffuse", material->gamma_diffuse);
				shader->set_uniform("material.gamma_specular", material->gamma_specular);

				gl.draw_renderable_unit(renderable_unit);

				shader->disable();
			}
		}
	}

	void Renderer::reshape_viewport(unsigned int width, unsigned int height) {
		gl.reshape_viewport(width, height);

		if (scene && scene->camera) {
			scene->camera->set_viewport(gl.get_viewport_width(), gl.get_viewport_height());
		}
	}

	void Renderer::toggle_wireframe_mode() {
		gl.toggle_wireframe_mode();
	}

	void Renderer::cache_resources() {
		shader_ids.clear();

		for (SlotmapKey scene_node_key : scene->renderable_objects_collection) {
			SceneNode* scene_node = scene->scene_nodes.get(scene_node_key);
			Object& scene_object = scene_node->object;
			Renderable* renderable = ComponentManager::get_renderable(scene_object.get_renderable_key());

			for (RenderableUnit* renderable_unit : renderable->renderable_units) {
				shader_ids.insert(renderable_unit->material->shader_id);
			}
		}
	}
}