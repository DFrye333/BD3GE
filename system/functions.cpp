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
	timeval beforeTime;
	timeval afterTime;
	double elapsedTime = 0.0;
	Cube boxanne = Cube(
			Vector3(0.0f, 0.0f, -3.0f),
			Vector3(0.75f, 0.75f, 0.75f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0);
	Cube boxanne2 = Cube(
			Vector3(-1.0f, 0.0f, -3.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			1.0);
	Cube* cubettes[2];

	cubettes[0] = &boxanne;
	cubettes[1] = &boxanne2;

	//    Main game loop
	// =====================
	gettimeofday(&beforeTime, NULL);
	while (1)
	{
		xWindow.messageListener();

		// Check timer.
		gettimeofday(&afterTime, NULL);
		// elapsedTime was adding the (afterTime - beforeTime) interval to itself every single iteration! That did *not* measure elapsed time! Below should now be correct.
		elapsedTime = ((afterTime.tv_sec - beforeTime.tv_sec) * 1000.0) + ((afterTime.tv_usec - beforeTime.tv_usec) / 1000.0);
		if (elapsedTime >= BD3GE_FRAME_TIME)
		{
			// Update and render.
			boxanne.move();
			gl.render(cubettes);

			// Display FPS.
			std::cout << "FPS: " << 1 / (elapsedTime / 1000.0) << std::endl;

			// Reset timer.
			gettimeofday(&beforeTime, NULL);
			elapsedTime = 0.0;
		}
	}
	// =====================
}
