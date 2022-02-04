#include "scene.h"

namespace BD3GE {
	Scene::Scene(const std::string modelsDirectory) {
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
		} else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Assimp scene loading failed...");
		}

		ShaderObject vertex_default = ShaderObject(GL_VERTEX_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert");
		ShaderObject vertex_texture = ShaderObject(GL_VERTEX_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.vert");
		ShaderObject vertex_material_simple = ShaderObject(GL_VERTEX_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/material_simple.vert");
		ShaderObject fragment_default = ShaderObject(GL_FRAGMENT_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/default.frag");
		ShaderObject fragment_texture = ShaderObject(GL_FRAGMENT_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.frag");
		ShaderObject fragment_material_simple = ShaderObject(GL_FRAGMENT_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/material_simple.frag");
		ShaderObject fragment_material_mapped = ShaderObject(GL_FRAGMENT_SHADER, DEFAULT_RESOURCE_DIRECTORY + "shaders/material_mapped.frag");
		Texture* wall_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/wall.jpg");
		Texture* container_diffuse_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/container_diffuse.png");
		Texture* container_specular_texture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/container_specular.png");

		// Scary duck
		SimpleMaterial* duck_material = new SimpleMaterial(new Shader(&vertex_material_simple, &fragment_material_simple), Color(255, 255, 0));
		this->scaryDuck = add_renderable(new Mesh(Vector3(0, 0, -500), duck->mMeshes[0], nullptr, duck_material, Vector3(1, 1, 1)));

		// Cube
		SimpleMaterial* cube_material = new SimpleMaterial(new Shader(&vertex_material_simple, &fragment_material_simple), Color(0, 255, 0));
		add_renderable(new Mesh(Vector3(-60, 0, 0), cube->mMeshes[0], nullptr, cube_material, Vector3(1, 1, 1)));

		// Floor
		MappedMaterial* brick_floor_material = new MappedMaterial(new Shader(&vertex_texture, &fragment_material_mapped), wall_texture, wall_texture, 32.0f);
		add_renderable(new SquareBrush(Vector3(-5, 5, 0), 10, 10, brick_floor_material));

		// Pillars
		SimpleMaterial* pillar_material = new SimpleMaterial(new Shader(&vertex_material_simple, &fragment_material_simple), Color(255, 0, 0));
		for (unsigned int i = 0; i < 121; ++i) {
			add_renderable(new BoxBrush(Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0), Vector3(2, 10, 2), pillar_material));
		}

		// Mapped container
		MappedMaterial* container_material = new MappedMaterial(new Shader(&vertex_texture, &fragment_material_mapped), container_diffuse_texture, container_specular_texture, 32.0f);
		add_renderable(new SquareBrush(Vector3(75, 0, 0), 5, 5, container_material));

		// Player
		SimpleMaterial* player_material = new SimpleMaterial(new Shader(&vertex_material_simple, &fragment_material_simple), Color(10, 51, 102));
		this->player = add_renderable(new BoxBrush(Vector3(5, 5, 0), Vector3(2, 2, 2), player_material));

		// Light
		SimpleMaterial* light_material = new SimpleMaterial(new Shader(&vertex_default, &fragment_default), Color(102, 229, 102));
		this->light = add_renderable(new CircularBrush(Vector3(5, 5, 100), 1.5, 10, light_material));

		Light light = Light(this->light->get_position(), Color(25, 25, 25), Color(128, 128, 128), Color(255, 255, 255));
		player_material->shader->addLight(light);
		pillar_material->shader->addLight(light);
		brick_floor_material->shader->addLight(light);
		container_material->shader->addLight(light);

		this->camera = new Camera(Vector3(0, 0, 300));
		//camera->rotate(Vector3(10 / (180 / BD3GE::PI), 0, 10 / (180 / BD3GE::PI)));
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
			camera->translate(Vector3(input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_X) * player_speed, 0, 0));
		}
		camera->translate(Vector3(input->get_key_state(BD3GE::KEY_CODE::LEFT) * -player_speed, 0, 0));
		camera->translate(Vector3(input->get_key_state(BD3GE::KEY_CODE::RIGHT) * player_speed, 0, 0));

		if (input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_Y) != 0) {
			camera->translate(Vector3(0, input->get_gamepad_input_value(primary_gamepad_index, Gamepad::INPUT_CODE::RIGHT_STICK_Y) * player_speed, 0));
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
			//camera->set_direction();
		}

		if (input->get_key_state(BD3GE::KEY_CODE::J)) {
			light->translate(Vector3(0.25 * -player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::L)) {
			light->translate(Vector3(0.25 * player_speed, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::I)) {
			light->translate(Vector3(0, 0.25 * player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::K)) {
			light->translate(Vector3(0, 0.25 * -player_speed, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::O)) {
			light->translate(Vector3(0, 0, 0.25 * player_speed));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::U)) {
			light->translate(Vector3(0, 0, 0.25 * -player_speed));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::KP_1)) {
			light->rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_3)) {
			light->rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_5)) {
			light->rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::KP_2)) {
			light->rotate(Vector3(0, -0.01, 0));
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

		for (Renderable* renderable : renderables) {
			for (Material* material : renderable->materials) {
				material->shader->setUniform("light.position", this->light->get_position());
				material->shader->setUniform("viewer_position", this->camera->get_position());
			}
		}

		scaryDuck->rotate(Vector3(0, 0.001, 0));
		//camera->rotate(Vector3(0, 0.1 / (180 / BD3GE::PI), 0));
	}

	void Scene::mouse_move(Input* input) {
		if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_LEFTBUTTON) && input->is_mouse_position_fresh) {
			std::pair<short, short> currentMousePosition = input->get_current_mouse_position();
			std::pair<short, short> previousMousePosition = input->get_previous_mouse_position();
			Vector3 currentMouseVector = Vector3(-currentMousePosition.first, currentMousePosition.second, 0);
			Vector3 previousMouseVector = Vector3(-previousMousePosition.first, previousMousePosition.second, 0);
			Vector3 mouseTranslation = currentMouseVector - previousMouseVector;
			if (mouseTranslation.get_magnitude() < 100) {
				camera->translate(mouseTranslation * 0.1);
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

	Camera* Scene::getCamera(void) {
		return camera;
	}
}