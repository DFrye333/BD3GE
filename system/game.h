#ifndef BD3GE_GAME_H
#define BD3GE_GAME_H

#include <sys/stat.h>
#include <sys/types.h>

//#include <sys/time.h>
#include <dirent.h>

#include "../audio/AL.h"
#include "../input/input.h"
#include "../utility/timer.h"
#include "../video/GL.h"
#include "../video/scene.h"
#include "../system/window.h"
#include "constants.h"
#include "globals.h"

namespace BD3GE {
	class Game {
		public:

					Game(BD3GE::Window* window);
					~Game();
			void	startup(BD3GE::Window* window);
			void	shutdown(void);
			void 	run(void);
			void	bus_messages(void);

		private:

			bool				m_running;
			Window*				m_window;
			Scene*				m_scene;
			GL*					m_GL;
			AL*					m_AL;
			Input*				m_input;
	};
}

#endif // BD3GE_GAME_H
