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
		}
		else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Assimp scene loading failed...");
		}

		// TODO: These should be owned by renderables.
		Shader* defaultShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/default.frag");
		Shader* lightingShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/lighting_point.frag");
		Shader* textureShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.frag");
		Texture* wallTexture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/wall.jpg");

		this->lightingShader = lightingShader;

		// Scary duck
		this->scaryDuck = add_object(new Object(
			Vector3(0, 0, -500),
			Vector3(0, 0, 0),
			new Mesh(duck->mMeshes[0], nullptr, lightingShader, Vector3(1, 1, 1))
		));

		// Cube
		add_object(new Object(
			Vector3(-60, 0, 0),
			Vector3(0, 0, 0),
			new Mesh(cube->mMeshes[0], nullptr, lightingShader, Vector3(1, 1, 1))
		));

		// Floor
		add_object(new Object(
			Vector3(-5, 5, 0),
			Vector3(0, 0, 0),
			new SquareBrush(10, 10, textureShader, wallTexture)
		));

		// Pillars
		for (unsigned int i = 0; i < 121; ++i) {
			add_object(new Object(
				Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0),
				Vector3(0, 0, 0),
				new SquareBrush(2, 2, lightingShader, Color(50, 160, 0))
			));
		}

		// Player
		this->player = add_object(new Object(
			Vector3(5, 5, 0),
			Vector3(0, 0, 0),
			new SquareBrush(2, 2, lightingShader, Color(10, 51, 102))
		));

		// Light
		this->light = add_light(new Object(
			Vector3(5, 5, 100),
			Vector3(0, 0, 0),
			new CircularBrush(1.5, 10, defaultShader, Color(102, 229, 102))
		));

		this->camera = new Camera(Vector3(0, 0, 60));
		//camera->rotate(Vector3(10 / (180 / BD3GE::PI), 0, 10 / (180 / BD3GE::PI)));
	}

	Scene::Scene(std::vector<Object*> objects) {
		objects = objects;
	}

	Scene::~Scene() {
		delete camera;
		camera = nullptr;

		for (std::vector<Object*>::size_type i = 0; i != objects.size(); ++i) {
			delete objects[i];
			objects[i] = nullptr;
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
		if (input->get_key_state(BD3GE::KEY_CODE::W) || input->get_gamepad_value(1, Gamepad::INPUT_CODE::LEFT_STICK_Y) > 0) {
			player->translate(Vector3(0, PLAYER_SPEED, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::S) || input->get_gamepad_value(1, Gamepad::INPUT_CODE::LEFT_STICK_Y) < 0) {
			player->translate(Vector3(0, -PLAYER_SPEED, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::A) || input->get_gamepad_value(1, Gamepad::INPUT_CODE::LEFT_STICK_X) < 0) {
			player->translate(Vector3(-PLAYER_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::D) || input->get_gamepad_value(1, Gamepad::INPUT_CODE::LEFT_STICK_X) > 0) {
			player->translate(Vector3(PLAYER_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::Q)) {
			player->translate(Vector3(0, 0, -PLAYER_SPEED));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::E)) {
			player->translate(Vector3(0, 0, PLAYER_SPEED));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::F)) {
			player->rotate(Vector3(0, 0, 0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::H)) {
			player->rotate(Vector3(0, 0, -0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::T)) {
			player->rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::G)) {
			player->rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::Y)) {
			player->rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::R)) {
			player->rotate(Vector3(0, -0.01, 0));
		}

		if (input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELUP) || input->get_gamepad_value(1, BD3GE::Gamepad::INPUT_CODE::RIGHT_TRIGGER)) {
			camera->translate(Vector3(0, 0, 2 * -CAMERA_SPEED));
		} else if (input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELDOWN) || input->get_gamepad_value(1, BD3GE::Gamepad::INPUT_CODE::LEFT_TRIGGER)) {
			camera->translate(Vector3(0, 0, 2 * CAMERA_SPEED));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_LEFTBUTTON) && input->is_mouse_position_fresh) {
			std::pair<short, short> currentMousePosition = input->get_current_mouse_position();
			std::pair<short, short> previousMousePosition = input->get_previous_mouse_position();
			Vector3 currentMouseVector = Vector3(-currentMousePosition.first, currentMousePosition.second, 0);
			Vector3 previousMouseVector = Vector3(-previousMousePosition.first, previousMousePosition.second, 0);
			Vector3 mouseTranslation = currentMouseVector - previousMouseVector;
			if (mouseTranslation.get_magnitude() < 10) {
				camera->translate(mouseTranslation * 0.1);
			}
		}

		if (input->get_key_state(BD3GE::KEY_CODE::R)) {
			camera->set_position(Vector3(0, 0, 60));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::J)) {
			light->translate(Vector3(0.25 * -PLAYER_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::L)) {
			light->translate(Vector3(0.25 * PLAYER_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::I)) {
			light->translate(Vector3(0, 0.25 * PLAYER_SPEED, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::K)) {
			light->translate(Vector3(0, 0.25 * -PLAYER_SPEED, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::O)) {
			light->translate(Vector3(0, 0, 0.25 * PLAYER_SPEED));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::U)) {
			light->translate(Vector3(0, 0, 0.25 * -PLAYER_SPEED));
		}

		camera->move();
		for (auto& object : objects) {
			object->move();
		}
		for (auto& light : lights) {
			light->move();
		}

		lightingShader->enable();
		lightingShader->setUniform("light_position", this->light->get_position());
		lightingShader->setUniform("light_color", Vector3(1.0, 0.1, 0.1));
		lightingShader->setUniform("viewer_position", this->camera->get_position());
		lightingShader->disable();

		scaryDuck->rotate(Vector3(0, 0.001, 0));
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