#ifndef BD3GE_GAME_H
#define BD3GE_GAME_H

#include <sys/stat.h>
#include <sys/types.h>

//#include <sys/time.h>

#include "../audio/AL.h"
#include "../input/gamepad.h"
#include "../input/input.h"
#include "../game/scene.h"
#include "../os/win32.h"
#include "../system/window.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/log.h"
#include "../utility/timer.h"
#include "../video/GL.h"
#include "../video/renderer.h"

namespace BD3GE {
	class Game {
		public:

					Game(Window* window);
					~Game();
			void 	run();
			void	bus_messages();

		private:

			Window*				window;
			Scene*				scene;
			Renderer*			renderer;
			AL*					al;
			Input*				input;
	};
}

#endif // BD3GE_GAME_H