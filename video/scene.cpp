#include "scene.h"

namespace BD3GE {
	/*
	 *	Scene class
	 */

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
		Shader* textureShader = new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/texture.frag");
		Texture* wallTexture = new Texture(DEFAULT_RESOURCE_DIRECTORY + "textures/wall.jpg");

		// Scary duck
		this->scaryDuck = add_object(new Object(
			Vector3(0, 0, -500),
			Vector3(0, 0, 0),
			new Mesh(duck->mMeshes[0], nullptr, defaultShader, Vector3(1, 1, 1))
		));

		// Cube
		add_object(new Object(
			Vector3(-60, 0, 0),
			Vector3(0, 0, 0),
			new Mesh(cube->mMeshes[0], nullptr, defaultShader, Vector3(1, 1, 1))
		));

		// Floor
		add_object(new Object(
			Vector3(-10, 10, 0),
			Vector3(0, 0, 0),
			new SquareBrush(20, 20, textureShader, wallTexture)
		));

		// Pillars
		for (unsigned int i = 0; i < 121; ++i) {
			add_object(new Object(
				Vector3((float)(10 * (i % 11)) - 50, (float)(10 * (i / 11)) - 50, 0),
				Vector3(0, 0, 0),
				new SquareBrush(2, 2, Color(Vector3(0.0f, 0.5f, 0.0f)))
			));
		}

		this->player = add_object(new Object(
			Vector3(5.0f, 5.0f, 0),
			Vector3(0, 0, 0),
			new CircularBrush(2.5, 10, Color(Vector3(0, 0.66f, 0.33f)))
		));

		this->camera = new Camera(Vector3(0, 0, 60));
		//camera->rotate(Vector3(-30, 0, 0));
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

	void Scene::tick(Input* input) {
		if ((!input->get_key_state(BD3GE::KEY_CODE::W) && !input->get_key_state(BD3GE::KEY_CODE::S)) || (input->get_key_state(BD3GE::KEY_CODE::W) && input->get_key_state(BD3GE::KEY_CODE::S))) {
			player->set_velocity_Y(0);
		} else if (input->get_key_state(BD3GE::KEY_CODE::W)) {
			player->set_velocity_Y(PLAYER_SPEED);
		} else if (input->get_key_state(BD3GE::KEY_CODE::S)) {
			player->set_velocity_Y(-PLAYER_SPEED);
		}

		if ((!input->get_key_state(BD3GE::KEY_CODE::A) && !input->get_key_state(BD3GE::KEY_CODE::D)) || (input->get_key_state(BD3GE::KEY_CODE::A) && input->get_key_state(BD3GE::KEY_CODE::D))) {
			player->set_velocity_X(0);
		} else if (input->get_key_state(BD3GE::KEY_CODE::A)) {
			player->set_velocity_X(-PLAYER_SPEED);
		} else if (input->get_key_state(BD3GE::KEY_CODE::D)) {
			player->set_velocity_X(PLAYER_SPEED);
		}

		if ((!input->get_key_state(BD3GE::KEY_CODE::Q) && !input->get_key_state(BD3GE::KEY_CODE::E)) || (input->get_key_state(BD3GE::KEY_CODE::Q) && input->get_key_state(BD3GE::KEY_CODE::E))) {
			player->set_velocity_Z(0);
		} else if (input->get_key_state(BD3GE::KEY_CODE::Q)) {
			player->set_velocity_Z(-PLAYER_SPEED);
		} else if (input->get_key_state(BD3GE::KEY_CODE::E)) {
			player->set_velocity_Z(PLAYER_SPEED);
		}

		if (input->get_key_state(BD3GE::KEY_CODE::J)) {
			player->rotate(Vector3(0, 0, 0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::L)) {
			player->rotate(Vector3(0, 0, -0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::I)) {
			player->rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::K)) {
			player->rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::U)) {
			player->rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::O)) {
			player->rotate(Vector3(0, -0.01, 0));
		}

		if (input->get_key_state(BD3GE::KEY_CODE::LEFT)) {
			camera->translate(Vector3(-CAMERA_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::RIGHT)) {
			camera->translate(Vector3(CAMERA_SPEED, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::UP)) {
			camera->translate(Vector3(0, CAMERA_SPEED, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::DOWN)) {
			camera->translate(Vector3(0, -CAMERA_SPEED, 0));
		}
		bool mouseWheelUp = input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELUP);
		bool mouseWheelDown = input->consume_key_input(BD3GE::KEY_CODE::MOUSE_WHEELDOWN);
		if (mouseWheelUp) {
			camera->translate(Vector3(0, 0, 2 * -CAMERA_SPEED));
		}
		else if (mouseWheelDown) {
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

		camera->move();
		for (std::vector<Object*>::size_type i = 0; i < objects.size(); ++i) {
			objects[i]->move();
		}

		scaryDuck->rotate(Vector3(0, 0.001, 0));
	}

	void Scene::render(void) {
		// Clear the color buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (std::vector<Object*>::size_type i = 0; i != objects.size(); ++i) {
			objects[i]->render(camera->get_view_projection_transform());
		}
	}

	Camera* Scene::getCamera(void) {
		return camera;
	}
}