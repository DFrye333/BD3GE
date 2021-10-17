#ifndef BD3GE_GAME_H
#define BD3GE_GAME_H

#include <sys/stat.h>
#include <sys/types.h>

//#include <sys/time.h>
#include <dirent.h>

#include "../audio/AL.h"
#include "../input/gamepad.h"
#include "../input/input.h"
#include "../utility/timer.h"
#include "../video/GL.h"
#include "../game/scene.h"
#include "../system/window.h"
#include "../system/constants.h"
#include "../system/globals.h"

namespace BD3GE {
	class Game {
		public:

					Game(BD3GE::Window* window);
					~Game();
			void 	run();
			void	bus_messages();

		private:

			Window*				window;
			Scene*				scene;
			GL*					gl;
			AL*					al;
			Input*				input;
			Gamepad*			gamepad;
	};
}

#endif // BD3GE_GAME_H
