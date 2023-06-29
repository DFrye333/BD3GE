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

		SlotmapKey skybox_key = this->scene->skybox_key;

		unsigned int renderable_units_count = 0;
		for (SlotmapKey scene_node_key : this->scene->renderable_objects_collection) {
			SceneNode* scene_node = this->scene->scene_nodes.get(scene_node_key);
			Object& scene_object = scene_node->object;
			Renderable* renderable = scene_object.get_renderable();

			// Lazy-loads renderables.
			if (renderable->renderable_units.empty()) {
				renderable = ModelManager::get_model(renderable->renderable_id);
				scene_object.set_renderable(ComponentManager::add_renderable(*renderable));
			}

			renderable_units_count += renderable->renderable_units.size();
		}
		for (SlotmapKey renderable_key : this->scene->renderable_keys) {
			Renderable* renderable = ComponentManager::get_renderable(renderable_key);

			renderable_units_count += renderable->renderable_units.size();
		}
		if (skybox_key.is_initialized()) {
			// TODO: Make this more dynamic.
			renderable_units_count += 6;
		}

		gl.create_buffers(renderable_units_count);

		for (SlotmapKey scene_node_key : this->scene->renderable_objects_collection) {
			SceneNode* scene_node = this->scene->scene_nodes.get(scene_node_key);
			Object& scene_object = scene_node->object;
			Renderable* renderable = ComponentManager::get_renderable(scene_object.get_renderable_key());

			setup_renderable(renderable);
		}
		for (SlotmapKey renderable_key : this->scene->renderable_keys) {
			Renderable* renderable = ComponentManager::get_renderable(renderable_key);

			setup_renderable(renderable);
		}

		if (skybox_key.is_initialized()) {
			Cubemap* skybox = (Cubemap*)(ComponentManager::get_renderable(skybox_key));
			gl.setup_vaos(skybox->renderable_units);
			gl.initialize_cubemap(skybox->renderable_id);
		}

		cache_resources();
	}

	void Renderer::render() {
		gl.clear_buffers();

		if (!scene || !scene->camera) { return; }

		Transform* camera_transform = scene->camera->get_world_transform();
		Matrix4 view_projection_transform = scene->camera->get_view_projection_matrix();

		SlotmapKey skybox_key = scene->skybox_key;
		if (skybox_key.is_initialized()) {
			Cubemap* skybox = (Cubemap*)(ComponentManager::get_renderable(skybox_key));
			gl.enable_cubemap(skybox->renderable_id, 2);
			for (RenderableUnit* renderable_unit : skybox->renderable_units) {
				Transform world_transform_stack = renderable_unit->build_transform_hierarchy();
				world_transform_stack = *camera_transform * world_transform_stack;

				CubeMappedMaterial* cube_mapped_material = (CubeMappedMaterial*)renderable_unit->material;
				Shader* shader = ShaderManager::get_shader(cube_mapped_material->shader_id);
				shader->enable();
				shader->set_uniform("world_transform", world_transform_stack.get_matrix());
				shader->set_uniform("view_projection_transform", view_projection_transform);
				gl.set_depth_testing(false);
				gl.draw_renderable_unit(renderable_unit);
				gl.set_depth_testing(true);
				shader->disable();
			}
		}

		float gamma = ConfigManager::get_config_value_float("gamma");
		bool enable_blinn_phong = ConfigManager::get_config_value_bool("enable_blinn_phong");

		Vector3 camera_position = camera_transform->get_position();
		std::vector<Light*> lights;
		for (SlotmapKey directional_light_key : scene->directional_light_keys) {
			lights.emplace_back(scene->get_directional_light(directional_light_key));
		}
		for (SlotmapKey point_light_key : scene->point_light_keys) {
			lights.emplace_back(scene->get_point_light(point_light_key));
		}
		for (SlotmapKey spot_light_key : scene->spot_light_keys) {
			lights.emplace_back(scene->get_spot_light(spot_light_key));
		}
		for (Light* light : lights) {
			for (size_t shader_id : shader_ids) {
				Shader* shader = ShaderManager::get_shader(shader_id);
				shader->set_light(light);
				shader->set_uniform("viewer_position", camera_position);
			}
		}

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
				Transform world_transform_stack = renderable_unit->build_transform_hierarchy();
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
					SimpleMaterial* simple_material = (SimpleMaterial*)renderable_unit->material;

					shader->set_uniform("is_material_mapped", false);
					shader->set_uniform("simple_material.color_ambient", simple_material->color_ambient.rgb);
					shader->set_uniform("simple_material.color_diffuse", simple_material->color_diffuse.rgb);
					shader->set_uniform("simple_material.color_specular", simple_material->color_specular.rgb);
				} else if (material->type == Material::TYPE::MAPPED) {
					MappedMaterial* mapped_material = (MappedMaterial*)renderable_unit->material;

					shader->set_uniform("is_material_mapped", true);
					shader->set_uniform("mapped_material.map_diffuse[0]", 0);
					shader->set_uniform("mapped_material.map_specular[0]", 1);

					gl.enable_texture(mapped_material->map_diffuse_id, 0);
					gl.enable_texture(mapped_material->map_specular_id, 1);
				} else if (material->type == Material::TYPE::CUBE_MAPPED) {
					CubeMappedMaterial* cube_mapped_material = (CubeMappedMaterial*)renderable_unit->material;

					// TODO: Support general cubemaps
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
	
	void Renderer::setup_renderable(Renderable* renderable) {
		gl.setup_vaos(renderable->renderable_units);

		for (RenderableUnit* renderable_unit : renderable->renderable_units) {
			Material* material = renderable_unit->material;
			if (material->type == Material::TYPE::MAPPED) {
				MappedMaterial* mapped_material = (MappedMaterial*)material;
				gl.initialize_texture(mapped_material->map_diffuse_id);
				gl.initialize_texture(mapped_material->map_specular_id);
			}
		}
	}
}