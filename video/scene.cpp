#include "scene.h"

namespace BD3GE
{
	/*
	 *	Scene class
	 */

	Scene::Scene(const std::string file_path)
	{
		Assimp::Importer importer;

		// Import asset residing at given file path.
		const aiScene* scene = importer.ReadFile(file_path, aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_FlipWindingOrder);

		// Ensure that asset importing succeeded.
		if (scene)
		{
			g_log.write("Assimp scene loading succeeded!", LOG_INFORMATION);
		}
		else
		{
			g_log.write("Assimp scene loading failed...", LOG_ERROR);
		}

		// Cube boxanne = Cube(
		// 		Vector3(-1.0f, 0.0f, -3.0f),
		// 		Vector3(0.75f, 0.75f, 0.75f),
		// 		Vector3(0.0f, 0.0f, 0.0f),
		// 		1.0f);
		// Cube boxanne2 = Cube(
		// 		Vector3(1.0f, 0.0f, -3.0f),
		// 		Vector3(1.0f, 0.0f, 0.0f),
		// 		Vector3(0.0f, 0.0f, 0.0f),
		// 		1.0f);

		// mScene->add_object(&boxanne);
		// mScene->add_object(&boxanne2);

		// Create new objects from meshes.
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
		{
			add_object(new Object(
				Vector3(0.0f, 0.0f, -3.0f),
				Vector3(0.75f, 0.75f, 0.75f),
				Vector3(0.0f, 0.0f, 0.0f),
				scene->mMeshes[i]
			));
		}
		add_object(new Object(
			Vector3(-1.0f, 0.0f, -3.0f),
			Vector3(0.75f, 0.75f, 0.75f),
			Vector3(0.0f, 0.0f, 0.0f),
			scene->mMeshes[0]
		));
		add_object(new Object(
			Vector3(1.0f, 0.0f, -3.0f),
			Vector3(0.75f, 0.75f, 0.75f),
			Vector3(0.0f, 0.0f, 0.0f),
			scene->mMeshes[0]
		));

		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i)
		{
			m_objects[i]->scale(0.25f);
		}
	}

	Scene::Scene(std::vector<Object*> objects)
	{
		m_objects = objects;
	}

	Scene::~Scene()
	{
		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i)
		{
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}

	void Scene::add_object(Object* object)
	{
		m_objects.push_back(object);
	}

	void Scene::tick(Input* input)
	{
		if ((false == input->get_key_state(KEY_W) && false == input->get_key_state(KEY_S)) || (true == input->get_key_state(KEY_W) && true == input->get_key_state(KEY_S)))
		{
			m_camera.set_velocity_Z(0);
		}
		else if (true == input->get_key_state(KEY_W))
		{
			m_camera.set_velocity_Z(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(KEY_S))
		{
			m_camera.set_velocity_Z(PLAYER_SPEED);
		}
		if ((false == input->get_key_state(KEY_A) && false == input->get_key_state(KEY_D)) || (true == input->get_key_state(KEY_A) && true == input->get_key_state(KEY_D)))
		{
			m_camera.set_velocity_X(0);
		}
		else if (true == input->get_key_state(KEY_A))
		{
			m_camera.set_velocity_X(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(KEY_D))
		{
			m_camera.set_velocity_X(PLAYER_SPEED);
		}
		if ((false == input->get_key_state(KEY_Q) && false == input->get_key_state(KEY_E)) || (true == input->get_key_state(KEY_Q) && true == input->get_key_state(KEY_E)))
		{
			m_camera.set_velocity_Y(0);
		}
		else if (true == input->get_key_state(KEY_Q))
		{
			m_camera.set_velocity_Y(-PLAYER_SPEED);
		}
		else if (true == input->get_key_state(KEY_E))
		{
			m_camera.set_velocity_Y(PLAYER_SPEED);
		}

		static unsigned int count = 0;
		++count;
		m_objects[1]->set_position_X(25.0f * cos(-(count / 25.0f)));
		m_objects[1]->set_position_Y(25.0f * sin(-(count / 25.0f)));
		m_objects[2]->set_position_X(25.0f * cos(count / 25.0f));
		m_objects[2]->set_position_Y(25.0f * sin(count / 25.0f));
		// for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i)
		// {
		// 	m_objects[i]->scale((count % 25) / 100.0f);
		// }

		m_camera.move();
		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i)
		{
			m_objects[i]->move();
		}
	}

	void Scene::render(void)
	{
		// Clear the color buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (std::vector<Object*>::size_type i = 0; i != m_objects.size(); ++i)
		{
			m_objects[i]->render(m_camera.get_view_projection_transform());
		}
	}

	Camera& Scene::getCamera(void)
	{
		return m_camera;
	}
}