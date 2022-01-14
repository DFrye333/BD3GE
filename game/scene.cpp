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

		Shader* defaultShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/default.frag");
		Shader* lightingShaderSimple = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/lighting_point_simple.frag");
		Shader* lightingShaderMapped = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/lighting_point_mapped.frag");
		Shader* textureShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.frag");
		Texture* wallTexture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/wall.jpg");
		MappedMaterial* containerMaterial = new MappedMaterial(DEFAULT_RESOURCE_DIRECTORY + "textures/container_diffuse.png", DEFAULT_RESOURCE_DIRECTORY + "textures/container_specular.png", 32.0f);
		shaders.insert(shaders.end(), { defaultShader, lightingShaderSimple, lightingShaderMapped, textureShader });
		textures.insert(textures.end(), { wallTexture });

		// Scary duck
		this->scaryDuck = add_object(new Object(
			Vector3(0, 0, -500),
			new Mesh(duck->mMeshes[0], nullptr, lightingShaderSimple, Vector3(1, 1, 1))
		));

		// Cube
		add_object(new Object(
			Vector3(-60, 0, 0),
			new Mesh(cube->mMeshes[0], nullptr, lightingShaderSimple, Vector3(1, 1, 1))
		));

		// Floor
		add_object(new Object(
			Vector3(-5, 5, 0),
			new SquareBrush(10, 10, textureShader, wallTexture)
		));

		// Pillars
		for (unsigned int i = 0; i < 121; ++i) {
			add_object(new Object(
				Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0),
				new BoxBrush(Vector3(2, 10, 2), lightingShaderSimple, Color(50, 160, 0))
			));
		}

		// Mapped container
		add_object(new Object(
			Vector3(75, 0, 0),
			new SquareBrush(5, 5, lightingShaderMapped, containerMaterial)
		));

		// Player
		this->player = add_object(new Object(
			Vector3(5, 5, 0),
			new BoxBrush(Vector3(2, 2, 2), lightingShaderSimple, Color(10, 51, 102))
		));

		// Light
		this->light = add_light(new Object(
			Vector3(5, 5, 100),
			new CircularBrush(1.5, 10, defaultShader, Color(102, 229, 102))
		));

		this->lightingShaderSimple = lightingShaderSimple;
		this->lightingShaderMapped = lightingShaderMapped;
		Light light = Light(this->light->get_position(), Color(255, 255, 255), Color(255, 255, 255), Color(255, 255, 255));
		lightingShaderSimple->addLight(light);
		lightingShaderMapped->addLight(light);

		this->camera = new Camera(Vector3(0, 0, 300));
		//camera->rotate(Vector3(10 / (180 / BD3GE::PI), 0, 10 / (180 / BD3GE::PI)));
	}

	Scene::Scene(std::vector<Object*> objects) {
		objects = objects;
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;

		for (auto& object : objects) {
			delete object;
			object = nullptr;
		}

		for (auto& shader : shaders) {
			delete shader;
			shader = nullptr;
		}

		for (auto& texture : textures) {
			delete texture;
			texture = nullptr;
		}
	}

	Object* Scene::add_object(Object* object) {
		objects.push_back(object);
		return object;
	}

	Object* Scene::add_light(Object* light) {
		lights.push_back(light);
		return light;
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

		lightingShaderSimple->setUniform("light.position", this->light->get_position());
		lightingShaderSimple->setUniform("viewer_position", this->camera->get_position());
		lightingShaderMapped->setUniform("light.position", this->light->get_position());
		lightingShaderMapped->setUniform("viewer_position", this->camera->get_position());

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

		for (auto& object : objects) {
			object->render(camera->get_view_projection_transform());
		}
		for (auto& light : lights) {
			light->render(camera->get_view_projection_transform());
		}
	}

	Camera* Scene::getCamera(void) {
		return camera;
	}
}