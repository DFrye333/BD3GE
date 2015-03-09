#include "game.h"

/*
 * 	Game class
 */

Game::Game()
{
	startup();
}

void Game::startup(void)
{
	std::cout << BD3GE_PRINT_INFORMATION << "Starting up BD3GE now..." << std::endl;

	mRunning = true;

	glewInit();
}

void Game::shutdown(void)
{
	std::cout << BD3GE_PRINT_INFORMATION << "Shutting down BD3GE now..." << std::endl;

	mRunning = false;
}

void Game::run(void)
{
	Cube boxanne = Cube(
			Vector3(-1.0f, 0.0f, -3.0f),
			Vector3(0.75f, 0.75f, 0.75f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0f);
	Cube boxanne2 = Cube(
			Vector3(1.0f, 0.0f, -3.0f),
			Vector3(1.0f, 0.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0f);

	mScene.addObject(&boxanne);
	mScene.addObject(&boxanne2);

	//    Main game loop
	// ========================================================================

	// Initialize the logic and rendering timers.
	double elapsedTime = 0.0;
	Timer renderTimer("Render", BD3GE_FRAME_TIME);
	Timer logicTimer("Logic", BD3GE_TICK_TIME);
	renderTimer.start();
	logicTimer.start();

	// Iterate endlessly (unless halted elsewhere).
	while (mRunning)
	{
		// Handle subsystem communication.
		busMessages();

		// Quit the program if the Escape key is pressed.
		if (mInput.getKeyState(BD3GE_KEY_ESCAPE))
		{
			shutdown();
			continue;
		}

		// Check logic timer.
		if (logicTimer.isDue())
		{
			// Process a logic tick.
			mScene.tick(&mInput);
		}

		// Check render timer.
		if (renderTimer.isDue(&elapsedTime))
		{
			// Process a rendering frame.
			mScene.render();

			// Swap the frame buffer.
			mXWindow.swapBuffers();

			// Display FPS.
//			std::cout << "FPS: " << 1 / (elapsedTime / 1000.0) << std::endl;
		}
	}
	// ========================================================================
}

void Game::busMessages(void)
{
	// Listen for X messages.
	mXWindow.messageListener();

	// Pass input events.
	Message< std::pair<char*, bool> > inputMessage = mXWindow.pullInputMessage();
	if (inputMessage.getData())
	{
		mInput.handler(inputMessage);
	}

	// Pass reshape events.
	Message< std::pair<int, int> > reshapeMessage = mXWindow.pullReshapeMessage();
	if (reshapeMessage.getData())
	{
		mGL.reshape(reshapeMessage.getData()->first, reshapeMessage.getData()->second);
	}
}
