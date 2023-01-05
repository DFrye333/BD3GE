#ifndef BD3GE_GAME_H
#define BD3GE_GAME_H

#include <sys/stat.h>
#include <sys/types.h>

//#include <sys/time.h>

#include "../audio/AL.h"
#include "../input/gamepad.h"
#include "../input/input.h"
#include "../game/scene.h"
#include "../management/config_manager.h"
#include "../os/win32.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../system/window.h"
#include "../utility/log.h"
#include "../utility/timer.h"
#include "../video/GL.h"
#include "../video/renderer.h"

namespace BD3GE {
	extern "C" class BD3GE_API Game {
		public:

			Game(Window::EntryArgs* entry_args);
			virtual ~Game();
			virtual void load_scene(Scene* scene);
			virtual void run();
			void bus_messages();
			virtual void tick() = 0;
			virtual void mouse_move() = 0;

		protected:

			Window*				window;
			Scene*				scene;
			Renderer*			renderer;
			AL*					al;
			Input*				input;
	};
}

#endif // BD3GE_GAME_H