#include "scene.h"

namespace BD3GE {
	Scene::Scene(const std::string modelsDirectory) : scary_duck(nullptr) {
		Assimp::Importer planeImporter;
		Assimp::Importer duckImporter;

		// Import asset residing at given file path.
		unsigned int importer_options = 
			aiProcess_CalcTangentSpace | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_Triangulate | 
			aiProcess_SortByPType | 
			aiProcess_FlipWindingOrder;

		const aiScene* plane = planeImporter.ReadFile(modelsDirectory + "plane.dae", importer_options);
		const aiScene* cube = planeImporter.ReadFile(modelsDirectory + "cube.dae", importer_options);
		const aiScene* duck = duckImporter.ReadFile(modelsDirectory + "duck.dae", importer_options);

		// Ensure that asset importing succeeded.
		if (plane && duck) {
			g_log.write(BD3GE::LOG_TYPE::INFO, "Assimp scene loading succeeded!");
			g_log.write(BD3GE::LOG_TYPE::INFO, "Loading mesh with:");
			g_log.write(BD3GE::LOG_TYPE::INFO, "\tVertices: " + std::to_string(duck->mMeshes[0]->mNumVertices));
			g_log.write(BD3GE::LOG_TYPE::INFO, "\tFaces: " + std::to_string(duck->mMeshes[0]->mNumFaces));
			if (duck->HasMaterials()) {
				g_log.write(BD3GE::LOG_TYPE::INFO, "\tMaterials Index: " + std::to_string(duck->mMeshes[0]->mMaterialIndex));
			}
		} else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Assimp scene loading failed...");
		}

		ShaderObject vertex_default = ShaderObject(GL_VERTEX_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert");
		ShaderObject fragment_default = ShaderObject(GL_FRAGMENT_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/default.frag");
		Texture* wall_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/wall.jpg");
		Texture* container_diffuse_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/container_diffuse.png");
		Texture* container_specular_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/container_specular.png");

		// Scary duck
		SimpleMaterial* scary_duck_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), duck->mMaterials[0]);
		this->scary_duck = add_renderable(new Mesh(Vector3(0, 0, -500), duck->mMeshes[0], nullptr, scary_duck_material, Vector3(1, 1, 1)));
		this->scary_duck->scale(Vector3(0.25f, 0.25f, 0.25f));
		lit_materials.push_back(scary_duck_material);

		// Little duck
		SimpleMaterial* little_duck_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), Color(0, 128, 128));
		srand(time(nullptr));
		for (unsigned int i = 0; i < 2500; ++i) {
			Renderable* little_duck = add_renderable(new Mesh(Vector3(-100 + (rand() % 100) - 10, (rand() % 100) - 10, (rand() % 100) - 10), duck->mMeshes[0], nullptr, little_duck_material, Vector3(1, 1, 1)));
			this->little_ducks.push_back(little_duck);
			little_duck->scale(Vector3(0.01f, 0.01f, 0.01f));
			little_duck->rotate(Vector3((rand() % 90) * (BD3GE::PI / 180), (rand() % 90) * (BD3GE::PI / 180), (rand() % 90) * (BD3GE::PI / 180)));
		}
		lit_materials.push_back(little_duck_material);

		// Cube
		SimpleMaterial* cube_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), cube->mMaterials[0]);
		add_renderable(new Mesh(Vector3(-60, 0, 0), cube->mMeshes[0], nullptr, cube_material, Vector3(1, 1, 1)));
		lit_materials.push_back(cube_material);

		// Floor
		MappedMaterial* brick_floor_material = new MappedMaterial(new Shader(&vertex_default, &fragment_default), wall_texture, wall_texture, 32.0f);
		add_renderable(new SquareBrush(Vector3(-5, 5, 0), 10, 10, brick_floor_material));
		lit_materials.push_back(brick_floor_material);

		// Pillars
		SimpleMaterial* pillar_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), Color(255, 0, 25));
		for (unsigned int i = 0; i < 121; ++i) {
			add_renderable(new BoxBrush(Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0), Vector3(2, 10, 2), pillar_material));
		}
		lit_materials.push_back(pillar_material);

		// Mapped container
		MappedMaterial* container_material = new MappedMaterial(new Shader(&vertex_default, &fragment_default), container_diffuse_texture, container_specular_texture, 32.0f);
		add_renderable(new SquareBrush(Vector3(75, 0, 0), 5, 5, container_material));
		lit_materials.push_back(container_material);

		// Player
		SimpleMaterial* player_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), Color(10, 51, 102));
		this->player = add_renderable(new BoxBrush(Vector3(5, 5, 0), Vector3(2, 2, 2), player_material));
		lit_materials.push_back(player_material);

		// Light
		SimpleMaterial* light_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), Color(102, 229, 102));
		this->light_renderable = add_renderable(new CircularBrush(Vector3(5, 5, 100), 1.5, 10, light_material));

		this->lights.push_back(new SpotLight("White Spot Light", this->light_renderable->get_position(), Vector3(0, 0, -1), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));
		this->lights.push_back(new PointLight("White Point Light", this->light_renderable->get_position(), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));
		this->lights.push_back(new PointLight("Blue Point Light", Vector3(-50, 50, 20), Color(25, 25, 25), Color(0, 0, 255), Color(255, 255, 255), 1.0f, 0.022, 0.0019f));
		this->lights.push_back(new DirectionalLight("White Directional Light", Vector3(-1, 0, 0), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255)));

		this->camera = new Camera(Vector3(0, 0, 300));
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;

		for (auto& renderable : renderables) {
			delete renderable;
			renderable = nullptr;
		}
	}

	Renderable* Scene::add_renderable(Renderable* renderable) {
		renderables.push_back(renderable);
		return renderable;
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
			// TODO: Finish this thought.
			//camera->set_direction();
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

		if (!this->lights.empty()) {
			((SpotLight*)this->lights[0])->position = this->light_renderable->get_position();
			for (Material* lit_material : lit_materials) {
				if (lit_material->shader) {
					for (Light* light : lights) {
						lit_material->shader->setLight(light);
					}
					lit_material->shader->setUniform("viewer_position", this->camera->get_position());
				}
			}
		}

		if (scary_duck != nullptr) {
			scary_duck->rotate(Vector3(0, 0.001, 0));
		}
		for (Renderable* little_duck : little_ducks) {
			little_duck->rotate(Vector3(0, 0.01, 0));
		}
		//camera->rotate(Vector3(0, 0.1 / (180 / BD3GE::PI), 0));
	}

	void Scene::mouse_move(Input* input) {
		if (input->is_mouse_position_fresh) {
			std::pair<short, short> current_mouse_position = input->get_current_mouse_position();
			std::pair<short, short> previous_mouse_position = input->get_previous_mouse_position();
			Vector3 current_mouse_vector = Vector3(-current_mouse_position.first, current_mouse_position.second, 0);
			Vector3 previous_mouse_vector = Vector3(-previous_mouse_position.first, previous_mouse_position.second, 0);
			Vector3 mouse_translation = current_mouse_vector - previous_mouse_vector;

			if (mouse_translation.get_magnitude() < 100) {
				Vector3 mouse_rotation = mouse_translation * (float)(180 / BD3GE::PI);
				camera->rotate(Vector3(-mouse_translation.v.g.y, mouse_translation.v.g.x, 0) * 0.0001);

				if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_LEFTBUTTON)) {
					camera->translate(mouse_translation * 0.1);
				}
			}
		}
	}

	void Scene::render(void) {
		// Clear the color buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& renderable : renderables) {
			renderable->render(camera->get_view_projection_transform());
		}
	}

	Camera* Scene::get_camera(void) {
		return camera;
	}
}