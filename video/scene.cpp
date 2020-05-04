#include "scene.h"

namespace BD3GE {
	/*
	 *	Scene class
	 */

	Scene::Scene(const std::string file_path)
	{
		Assimp::Importer importer;

		// Import asset residing at given file path.
		unsigned int importer_options = 
			aiProcess_CalcTangentSpace | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_Triangulate | 
			aiProcess_SortByPType | 
			aiProcess_FlipWindingOrder;
		const aiScene* scene = importer.ReadFile(file_path, importer_options);

		// Ensure that asset importing succeeded.
		if (scene) {
			g_log.write(BD3GE::LOG_TYPE::INFO, "Assimp scene loading succeeded!");
		}
		else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Assimp scene loading failed...");
		}

		// Create new objects from meshes.
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
		{
			add_object(new Object(
				Vector3(0.0f, 0.0f, 0.0f),
				Vector3(0.75f, 0.75f, 0.75f),
				Vector3(0.0f, 0.0f, 0.0f),
				scene->mMeshes[i]
			));
		}
	}

	Scene::Scene(std::vector<Object*> objects) {
		m_objects = objects;
	}

	Scene::~Scene() {
		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i) {
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}

	void Scene::add_object(Object* object) {
		m_objects.push_back(object);
	}

	void Scene::tick(Input* input) {
		if ((false == input->get_key_state(BD3GE::KEY_CODE::W) && false == input->get_key_state(BD3GE::KEY_CODE::S)) || (true == input->get_key_state(BD3GE::KEY_CODE::W) && true == input->get_key_state(BD3GE::KEY_CODE::S))) {
			m_camera.set_velocity_Z(0);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::W)) {
			m_camera.set_velocity_Z(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::S)) {
			m_camera.set_velocity_Z(PLAYER_SPEED);
		}

		if ((false == input->get_key_state(BD3GE::KEY_CODE::A) && false == input->get_key_state(BD3GE::KEY_CODE::D)) || (true == input->get_key_state(BD3GE::KEY_CODE::A) && true == input->get_key_state(BD3GE::KEY_CODE::D))) {
			m_camera.set_velocity_X(0);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::A)) {
			m_camera.set_velocity_X(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::D)) {
			m_camera.set_velocity_X(PLAYER_SPEED);
		}

		if ((false == input->get_key_state(BD3GE::KEY_CODE::Q) && false == input->get_key_state(BD3GE::KEY_CODE::E)) || (true == input->get_key_state(BD3GE::KEY_CODE::Q) && true == input->get_key_state(BD3GE::KEY_CODE::E))) {
			m_camera.set_velocity_Y(0);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::Q)) {
			m_camera.set_velocity_Y(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(BD3GE::KEY_CODE::E)) {
			m_camera.set_velocity_Y(PLAYER_SPEED);
		}

		if (input->get_key_state(BD3GE::KEY_CODE::LEFT)) {
			m_camera.rotate(Vector3(0, 0, 0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::RIGHT)) {
			m_camera.rotate(Vector3(0, 0, -0.01));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::UP)) {
			m_camera.rotate(Vector3(-0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::DOWN)) {
			m_camera.rotate(Vector3(0.01, 0, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_LEFTBUTTON)) {
			m_camera.rotate(Vector3(0, 0.01, 0));
		}
		if (input->get_key_state(BD3GE::KEY_CODE::MOUSE_RIGHTBUTTON)) {
			m_camera.rotate(Vector3(0, -0.01, 0));
		}

		m_camera.move();
		for (std::vector<Object*>::size_type i = 0; i < m_objects.size(); ++i) {
			m_objects[i]->move();
		}
	}

	void Scene::render(void) {
		// Clear the color buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i) {
			m_objects[i]->render(m_camera.get_view_projection_transform());
		}
	}

	Camera& Scene::getCamera(void) {
		return m_camera;
	}
}
