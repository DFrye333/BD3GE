#include "scene.h"

namespace BD3GE {
	Scene::Scene() : scary_duck(nullptr), earth(nullptr), backpack(nullptr) {
		size_t no_light_shader_id = ShaderManager::compile_shader(ShaderManifest("default.vert", "default.frag"));
		size_t light_shader_id = ShaderManager::compile_shader(ShaderManifest("light.vert", "light.frag"));

		size_t wall_texture_id = TextureManager::load_texture("wall.jpg");
		size_t container_diffuse_texture_id = TextureManager::load_texture("container_diffuse.png");
		size_t container_specular_texture_id = TextureManager::load_texture("container_specular.png");
		size_t backpack_diffuse_texture_id = TextureManager::load_texture("1001_albedo.jpg");
		size_t backpack_specular_texture_id = TextureManager::load_texture("1001_metallic.jpg");
		size_t duck_texture_id = TextureManager::load_texture("duckCM.tga");

		size_t backpack_model_id = ModelManager::load_model("Survival_BackPack_2.fbx");
		size_t duck_model_id = ModelManager::load_model("duck.dae");
		size_t cube_model_id = ModelManager::load_model("cube.dae");
		size_t earth_model_id = ModelManager::load_model("earthCylindrical.dae");

		// Backpack
		this->backpack = add_renderable_object(new RenderableObject(Vector3(75, 50, 0), backpack_model_id));
		this->backpack->set_scale(Vector3(0.1f, 0.1f, 0.1f));
		this->backpack->renderable = ModelManager::get_model(backpack_model_id);
		for (RenderableUnit* renderable_unit : this->backpack->renderable->renderable_units) {
			((MappedMaterial*)renderable_unit->material)->map_diffuse_id = backpack_diffuse_texture_id;
			((MappedMaterial*)renderable_unit->material)->map_specular_id = backpack_specular_texture_id;
			lit_materials.push_back(renderable_unit->material);
		}

		// Scary duck
		this->scary_duck = add_renderable_object(new RenderableObject(Vector3(0, 0, -500), duck_model_id));
		this->scary_duck->set_scale(Vector3(50.0f, 50.0f, 50.0f));

		// Little ducks
		srand(time(nullptr));
		for (unsigned int i = 0; i < 2500; ++i) {
			RenderableObject* little_duck = add_renderable_object(new RenderableObject(Vector3(-100 + (rand() % 100) - 10, (rand() % 100) - 10, (rand() % 100) - 10), duck_model_id));
			this->little_ducks.push_back(little_duck);
			little_duck->rotate(Vector3((rand() % 90) * (BD3GE::PI / 180), (rand() % 90) * (BD3GE::PI / 180), (rand() % 90) * (BD3GE::PI / 180)));
		}

		// Cube
		RenderableObject* cube = add_renderable_object(new RenderableObject(Vector3(0, -60, 0), cube_model_id));

		// Earth
		this->earth = add_renderable_object(new RenderableObject(Vector3(75, -25, 0), earth_model_id));
		this->earth->set_scale(Vector3(50.0f, 50.0f, 50.0f));
		this->earth->rotate(Vector3(0, 0, BD3GE::PI / 32));

		// Floor
		MappedMaterial* tile_floor_material = new MappedMaterial(light_shader_id, wall_texture_id, wall_texture_id, 32.0f);
		Renderable* tile_floor_brush_renderable = new Renderable();
		tile_floor_brush_renderable->renderable_units.push_back(new RectangleBrush(tile_floor_material, Vector3(-5, 5, 0), 10, 10));
		add_renderable_object(new RenderableObject(Vector3(-5, 5, 0), tile_floor_brush_renderable));

		// Pillars
		SimpleMaterial* pillar_material = new SimpleMaterial(light_shader_id, Color(255, 0, 25));
		for (unsigned int i = 0; i < 121; ++i) {
			Vector3 position = Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0);
			Renderable* pillar_renderable = new Renderable();
			pillar_renderable->renderable_units.push_back(new BoxBrush(pillar_material, position, Vector3(2, 10, 2)));
			add_renderable_object(new RenderableObject(position, pillar_renderable));
		}

		// Mapped container
		MappedMaterial* container_material = new MappedMaterial(light_shader_id, container_diffuse_texture_id, container_specular_texture_id, 32.0f);
		Renderable* container_brush_renderable = new Renderable();
		container_brush_renderable->renderable_units.push_back(new RectangleBrush(container_material, Vector3(75, 0, 0), 5, 5));
		add_renderable_object(new RenderableObject(Vector3(75, 0, 0), container_brush_renderable));

		// Player
		SimpleMaterial* player_material = new SimpleMaterial(light_shader_id, Color(10, 51, 102));
		Renderable* player_brush_renderable = new Renderable();
		player_brush_renderable->renderable_units.push_back(new BoxBrush(player_material, Vector3(5, 5, 0), Vector3(2, 2, 2)));
		this->player = add_renderable_object(new RenderableObject(Vector3(5, 5, 0), player_brush_renderable));

		// Light
		SimpleMaterial* light_material = new SimpleMaterial(no_light_shader_id, Color(102, 229, 102));
		Renderable* light_brush_renderable = new Renderable();
		light_brush_renderable->renderable_units.push_back(new CircularBrush(light_material, Vector3(5, 5, 100), 1.5, 10));
		this->light_renderable = add_renderable_object(new RenderableObject(Vector3(5, 5, 100), light_brush_renderable));

		this->lights.push_back(new SpotLight("White Spot Light", this->light_renderable->get_position(), Vector3(0, 0, -1), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));
		this->lights.push_back(new PointLight("White Point Light", this->light_renderable->get_position(), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));
		this->lights.push_back(new PointLight("Blue Point Light", Vector3(-50, 50, 20), Color(25, 25, 25), Color(0, 0, 255), Color(255, 255, 255), 1.0f, 0.022, 0.0019f));
		this->lights.push_back(new DirectionalLight("White Directional Light", Vector3(-1, 0, 0), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));

		this->camera = new Camera(Vector3(0, 0, 300));
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;
	}

	RenderableObject* Scene::add_renderable_object(RenderableObject* renderable_object) {
		renderable_objects.push_back(renderable_object);
		return renderable_object;
	}

	void Scene::tick(Input* input) {
		short primary_gamepad_index = input->get_primary_connected_gamepad_index();

		float player_speed = PLAYER_SPEED;
		if (input->get_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::LEFT_TRIGGER)) {
			player_speed /= 4;
		} else if (input->get_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::RIGHT_TRIGGER)) {
			player_speed *= 2;
		}

		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_X) != 0) {
			player->translate(Vector3(input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_X) * player_speed, 0, 0));
			camera->translate(Vector3(input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_X) * player_speed, 0, 0));
		}
		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_Y) != 0) {
			player->translate(Vector3(0, input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_Y) * player_speed, 0));
			camera->translate(Vector3(0, input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::LEFT_STICK_Y) * player_speed, 0));
		}

		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_X) != 0) {
			light_renderable->translate(Vector3(input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_X) * player_speed, 0, 0));
		}
		camera->translate(Vector3(input->get_key_state(BD3GE::KEY_CODE::LEFT) * -player_speed, 0, 0));
		camera->translate(Vector3(input->get_key_state(BD3GE::KEY_CODE::RIGHT) * player_speed, 0, 0));

		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_Y) != 0) {
			light_renderable->translate(Vector3(0, input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_Y) * player_speed, 0));
		}
		camera->translate(Vector3(0, input->get_key_state(BD3GE::KEY_CODE::UP) * player_speed, 0));
		camera->translate(Vector3(0, input->get_key_state(BD3GE::KEY_CODE::DOWN) * -player_speed, 0));

		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::DPAD_UP)) {
			player->translate(Vector3(0, player_speed, 0));
		}
		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::DPAD_DOWN)) {
			player->translate(Vector3(0, -player_speed, 0));
		}
		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::DPAD_LEFT)) {
			player->translate(Vector3(-player_speed, 0, 0));
		}
		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::DPAD_RIGHT)) {
			player->translate(Vector3(player_speed, 0, 0));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::W)) {
			player->translate(Vector3(0, player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::S)) {
			player->translate(Vector3(0, -player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::A)) {
			player->translate(Vector3(-player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::D)) {
			player->translate(Vector3(player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::Q)) {
			player->translate(Vector3(0, 0, -player_speed));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::E)) {
			player->translate(Vector3(0, 0, player_speed));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::G)) {
			player->rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::B)) {
			player->rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::V)) {
			player->rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::N)) {
			player->rotate(Vector3(0, -0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::F)) {
			player->rotate(Vector3(0, 0, 0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::H)) {
			player->rotate(Vector3(0, 0, -0.01));
		}

		if (input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELUP) || input->get_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::RIGHT_SHOULDER)) {
			camera->translate(Vector3(0, 0, 2 * -CAMERA_SPEED));
		} else if (input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELDOWN) || input->get_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::LEFT_SHOULDER)) {
			camera->translate(Vector3(0, 0, 2 * CAMERA_SPEED));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::R)) {
			camera->set_position(Vector3(0, 0, 300));
			camera->set_orientation(Vector3(0, 0, 0));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::J)) {
			light_renderable->translate(Vector3(0.25 * -player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::L)) {
			light_renderable->translate(Vector3(0.25 * player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::I)) {
			light_renderable->translate(Vector3(0, 0.25 * player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::K)) {
			light_renderable->translate(Vector3(0, 0.25 * -player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::O)) {
			light_renderable->translate(Vector3(0, 0, 0.25 * player_speed));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::U)) {
			light_renderable->translate(Vector3(0, 0, 0.25 * -player_speed));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::KP_1)) {
			light_renderable->rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_3)) {
			light_renderable->rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_5)) {
			light_renderable->rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_2)) {
			light_renderable->rotate(Vector3(0, -0.01, 0));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::DEL)) {
			input->set_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_0, input->get_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_0) - 0.001);
		}
		if (input->get_key_state(BD3GE::KEY_CODE::INSERT)) {
			input->set_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_0, input->get_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_0) + 0.001);
		}
		if (input->get_key_state(BD3GE::KEY_CODE::PAGEUP)) {
			input->set_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_1, input->get_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_1) + 0.001);
		}
		if (input->get_key_state(BD3GE::KEY_CODE::PAGEDOWN)) {
			input->set_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_1, input->get_gamepad_output_value(primary_gamepad_index, Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_1) - 0.001);
		}

		if (input->get_key_state(BD3GE::KEY_CODE::P)) {
			camera->rotate(Vector3(1, 0, 0));
		}
		
		if (input->consume_key_input(BD3GE::KEY_CODE::NUM_1)) {
			lights[0]->is_active = !lights[0]->is_active;
		}
		if (input->consume_key_input(BD3GE::KEY_CODE::NUM_2)) {
			lights[1]->is_active = !lights[1]->is_active;
		}
		if (input->consume_key_input(BD3GE::KEY_CODE::NUM_3)) {
			lights[2]->is_active = !lights[2]->is_active;
		}
		if (input->consume_key_input(BD3GE::KEY_CODE::NUM_4)) {
			lights[3]->is_active = !lights[3]->is_active;
		}

		if (scary_duck) {
			scary_duck->rotate(Vector3(0, 0.001, 0));
		}
		if (earth) {
			earth->rotate(Vector3(0, 0.1 / (180 / BD3GE::PI), 0));
		}
		if (backpack) {
			backpack->rotate(Vector3(0, -(0.2 / (180 / BD3GE::PI)), 0));
		}
		for (RenderableObject* little_duck : little_ducks) {
			little_duck->rotate(Vector3(0, 0.01, 0));
		}

		((SpotLight*)this->lights[0])->position = this->light_renderable->get_position();
	}

	void Scene::mouse_move(Input* input) {
		if (input->is_mouse_position_fresh) {
			std::pair<short, short> current_mouse_position = input->get_current_mouse_position();
			std::pair<short, short> previous_mouse_position = input->get_previous_mouse_position();
			Vector3 current_mouse_vector = Vector3(-current_mouse_position.first, current_mouse_position.second, 0);
			Vector3 previous_mouse_vector = Vector3(-previous_mouse_position.first, previous_mouse_position.second, 0);
			Vector3 mouse_translation = current_mouse_vector - previous_mouse_vector;

			if (mouse_translation.get_magnitude() < 500) {
				Vector3 mouse_rotation = mouse_translation * (float)(180 / BD3GE::PI);
				camera->rotate(Vector3(-mouse_translation.v.g.y, mouse_translation.v.g.x, 0) * 0.0001);

				if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_LEFTBUTTON)) {
					camera->translate(mouse_translation * 0.1);
				}
			}
		}
	}
}