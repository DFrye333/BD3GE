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

	gettimeofday(&beforeTime, NULL);
	while (1)
	{
		//    Main game loop
		// =====================
		xWindow.messageListener();
		gettimeofday(&afterTime, NULL);
		elapsedTime += ((afterTime.tv_sec - beforeTime.tv_sec) * 1000.0) + ((afterTime.tv_usec - beforeTime.tv_usec) / 1000.0);
		if (elapsedTime >= BD3GE_FRAME_RATE)
		{
			boxanne.move();
//			boxanne2.move();
			gettimeofday(&beforeTime, NULL);
//			std::cout << "FPS: " << 1 / (elapsedTime / 1000.0) << std::endl;
			elapsedTime = 0.0;
			gl.render(cubettes);
		}
		// =====================
	}
}
