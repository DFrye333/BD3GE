#include "functions.h"

void init(void)
{
	std::cout << BD3GE_PRINT_INFORMATION << "Initializing BD3GE now..." << std::endl;

	gl.init();
	al.init();
	glewInit();
}

void quit(void)
{
	al.quit();

	std::cout << BD3GE_PRINT_INFORMATION << "Exiting BD3GE now..." << std::endl;
	exit(0);
}

void run(void)
{
	double elapsedTime = 0.0;
	Cube boxanne = Cube(
			Vector3(0.0f, 0.0f, -3.0f),
			Vector3(0.75f, 0.75f, 0.75f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0f);
	Cube boxanne2 = Cube(
			Vector3(-1.0f, 0.0f, -3.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0f);
	Scene scene;
	scene.addObject(&boxanne);
	scene.addObject(&boxanne2);

	//    Main game loop
	// =====================

	// Initialize the logic and rendering timers.
	Timer renderTimer("Render", BD3GE_FRAME_TIME);
	Timer logicTimer("Logic", BD3GE_TICK_TIME);
	renderTimer.start();
	logicTimer.start();

	// Iterate endlessly (unless halted elsewhere).
	while (1)
	{
		// Listen for X messages.
		xWindow.messageListener();

		// Check logic timer.
		if (logicTimer.isDue())
		{
			// Process a logic tick.
			boxanne.move();
		}

		// Check render timer.
		if (renderTimer.isDue(&elapsedTime))
		{
			// Process a rendering frame.
			gl.render(scene);

			// Display FPS.
			std::cout << "FPS: " << 1 / (elapsedTime / 1000.0) << std::endl;
		}
	}
	// =====================
}
