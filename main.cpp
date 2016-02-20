#include "system/game.h"

int main()
{
	BD3GE::Game game;
	game.startup();
	game.run();
	game.shutdown();

	return 0;
}
