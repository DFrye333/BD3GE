#include "scene.h"

/*
 * 	Scene class
 */

Scene::Scene()
{
}

Scene::Scene(std::vector<Object*> objects)
{
	mObjects = objects;
}

Scene::~Scene()
{
}

void Scene::addObject(Object* object)
{
	mObjects.push_back(object);
}

void Scene::tick(Input* input)
{
	if ((false == input->getKeyState(BD3GE_KEY_W) && false == input->getKeyState(BD3GE_KEY_S)) || (true == input->getKeyState(BD3GE_KEY_W) && true == input->getKeyState(BD3GE_KEY_S)))
	{
		mObjects[0]->setVelocityY(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_W))
	{
		mObjects[0]->setVelocityY(BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_S))
	{
		mObjects[0]->setVelocityY(-BD3GE_PLAYER_SPEED);
	}
	if ((false == input->getKeyState(BD3GE_KEY_A) && false == input->getKeyState(BD3GE_KEY_D)) || (true == input->getKeyState(BD3GE_KEY_A) && true == input->getKeyState(BD3GE_KEY_D)))
	{
		mObjects[0]->setVelocityX(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_A))
	{
		mObjects[0]->setVelocityX(-BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_D))
	{
		mObjects[0]->setVelocityX(BD3GE_PLAYER_SPEED);
	}
	if ((false == input->getKeyState(BD3GE_KEY_Q) && false == input->getKeyState(BD3GE_KEY_E)) || (true == input->getKeyState(BD3GE_KEY_Q) && true == input->getKeyState(BD3GE_KEY_E)))
	{
		mObjects[0]->setVelocityZ(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_Q))
	{
		mObjects[0]->setVelocityZ(-BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_E))
	{
		mObjects[0]->setVelocityZ(BD3GE_PLAYER_SPEED);
	}

	if ((false == input->getKeyState(BD3GE_KEY_UP) && false == input->getKeyState(BD3GE_KEY_DOWN)) || (true == input->getKeyState(BD3GE_KEY_UP) && true == input->getKeyState(BD3GE_KEY_DOWN)))
	{
		mObjects[1]->setVelocityY(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_UP))
	{
		mObjects[1]->setVelocityY(BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_DOWN))
	{
		mObjects[1]->setVelocityY(-BD3GE_PLAYER_SPEED);
	}
	if ((false == input->getKeyState(BD3GE_KEY_LEFT) && false == input->getKeyState(BD3GE_KEY_RIGHT)) || (true == input->getKeyState(BD3GE_KEY_LEFT) && true == input->getKeyState(BD3GE_KEY_RIGHT)))
	{
		mObjects[1]->setVelocityX(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_LEFT))
	{
		mObjects[1]->setVelocityX(-BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_RIGHT))
	{
		mObjects[1]->setVelocityX(BD3GE_PLAYER_SPEED);
	}
	if ((false == input->getKeyState(BD3GE_KEY_PRIOR) && false == input->getKeyState(BD3GE_KEY_NEXT)) || (true == input->getKeyState(BD3GE_KEY_PRIOR) && true == input->getKeyState(BD3GE_KEY_NEXT)))
	{
		mObjects[1]->setVelocityZ(0);
	}
	else if (true == input->getKeyState(BD3GE_KEY_PRIOR))
	{
		mObjects[1]->setVelocityZ(-BD3GE_PLAYER_SPEED);
	}
	else if (true == input->getKeyState(BD3GE_KEY_NEXT))
	{
		mObjects[1]->setVelocityZ(BD3GE_PLAYER_SPEED);
	}

	for (std::vector<Object*>::size_type i = 0; i != mObjects.size(); ++i)
	{
		mObjects[i]->move();
	}
}

void Scene::render(void)
{
	// Clear the color buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<Object*>::size_type i = 0; i != mObjects.size(); ++i)
	{
		mObjects[i]->render();
	}
}
